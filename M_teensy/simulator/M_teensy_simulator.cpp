#include "M_teensy_simulator.h"
#include <sndfile.h>
#include <time.h>

tm_context global_cxt;

IMPLEMENT_LINKED_LIST(et_msg_timed);

et_msg_timed_linked_list *message_list = NULL;

te_msg teensy_i2c_response;
uint8_t simulated_i2c_send_buffer[ET_MESSAGE_MAX_LEN];

SF_INFO sfinfo_out;
SNDFILE *outfile = NULL;

FILE *control_logfile;
FILE *transformer_logfile;

int ask_for_response = 0;

void run_teensy_init()
{
	tm_printf("Initialising memory pools... ");
	init_mem_pools();
	tm_printf("done.\n");
	
	tm_printf("Initialising context struct... ");
	init_tm_context(&global_cxt);
	tm_printf("done.\n");
}

void run_teensy_loop()
{
	profile_update(&global_cxt.profiles[global_cxt.active_profile]);
	esp32_message_check_handle();
	if (ask_for_response)
	{
		i2c_request_isr();
		ask_for_response = 0;
	}
	cxt_process(&global_cxt);
}

void add_message_to_queue(et_msg msg, int block_no)
{
	et_msg_timed tmsg;
	
	tmsg.msg = msg;
	tmsg.block_no = block_no;
	
	message_list = et_msg_timed_linked_list_append(message_list, tmsg);
}

void generate_msg_queue()
{
	add_message_to_queue(create_et_msg(ET_MESSAGE_APPEND_TRANSFORMER, "ss", 0, TRANSFORMER_DISTORTION), 64);
	add_message_to_queue(create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf", 0, 0, 0, 0.0), 128);
	add_message_to_queue(create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf", 0, 0, 0, 2.0), 256);
	add_message_to_queue(create_et_msg(ET_MESSAGE_SET_PARAM_VALUE, "sssf", 0, 0, 0, 5.0), 512);
}

et_msg generate_random_msg()
{
	et_msg msg;
	
	msg.type = rand() % ET_MESSAGE_TYPE_MAX;
	
	int len = et_message_data_length(msg);
	
	for (int i = 0; i < len; i++)
		msg.data[i] = rand() % ((rand() % 32) + 1);
	
	return msg;
}

#define ST_MESSAGE_INV_FREQ 10

void generate_stress_test_msg_queue(int n)
{
	srand(time(0));
	
	for (int i = 0; i < n; i++)
	{
		if (rand() % ST_MESSAGE_INV_FREQ == 0)
			add_message_to_queue(generate_random_msg(), i);
	}
}

int tmsim_send_et_msg(et_msg msg)
{
	printf("Sending message to simulated teensy...\n");
	int len = encode_et_msg(simulated_i2c_send_buffer, msg);
	
	i2c_recieve_isr(len);
	
	ask_for_response = 1;
	
	return NO_ERROR;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Please provide an output file name\n");
		abort();
	}
	
	sfinfo_out.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
	sfinfo_out.channels = 1;
	sfinfo_out.samplerate = 44100;
	
	char wavfile_buffer[128];
	char logfile_buffer[128];
	snprintf(wavfile_buffer, 128, "%s.wav", argv[1]);
	
	snprintf(logfile_buffer, 128, "%s.clog", argv[1]);
	control_logfile = fopen(logfile_buffer, "w");
	
	snprintf(logfile_buffer, 128, "%s.tlog", argv[1]);
	transformer_logfile = fopen(logfile_buffer, "w");
	
	outfile = sf_open(wavfile_buffer, SFM_WRITE, &sfinfo_out);
	
	if (!outfile)
	{
		printf("Failed to open %s\n", argv[1]);
		abort();
	}
	
	int n_blocks = 1 << 14;
	
	run_teensy_init();
	generate_msg_queue();
	
	et_msg_timed_linked_list *current = message_list;
	et_msg_timed_linked_list *next = next = current ? current->next : NULL;
	
	for (int i = 0; i < n_blocks; i++)
	{
		if (current)
		{
			if (i >= current->data.block_no)
			{
				tmsim_send_et_msg(current->data.msg);
				free(current);
				current = next;
				next = current ? current->next : NULL;
			}
		}
		
		run_teensy_loop();
		print_context_info(&global_cxt, -1);
	}
	
	sf_close(outfile);
	
	fclose(control_logfile);
	fclose(transformer_logfile);
	
	return 0;
}

#define RECORD

int tmsim_get_input_block(int16_t *block)
{
	#ifdef RECORD
	static uint32_t n_samples = 0;
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		block[i] = (1 << 15) * 0.5 * sinf(PI * n_samples * (440.0 * SAMPLE_FREQUENCY));
		n_samples++;
	}
	#endif
	return NO_ERROR;
}

uint32_t blocks_recieved = 0;
uint32_t samples_recieved = 0;

int tmsim_send_output_block(float *buffer)
{
	blocks_recieved++;
	sf_writef_float(outfile, buffer, AUDIO_BLOCK_SAMPLES);
	return NO_ERROR;
}

void profile_dump(tm_profile *profile)
{
	
}

void distortion_dump(tm_distortion_str *str)
{
	fprintf(transformer_logfile, "DISTORTION: sample %04d, gain = %f, wet mix = %f, bass mix = %f, mid mix = %f, high mix = %f, ",
		str->total_samples, str->gain.value, str->wet_mix.value, str->bass_mix.value, str->mid_mix.value, str->high_mix.value);
	fprintf(transformer_logfile, "low pass biquads: [%f, %f, %f, %f, %f], [[%f, %f], [%f, %f]]",
		str->low_pass_1.a0, str->low_pass_1.a1, str->low_pass_1.a2, str->low_pass_1.a3, str->low_pass_1.a4,
		str->low_pass_1.x1, str->low_pass_1.x2, str->low_pass_1.y1, str->low_pass_1.y2);
	
	
	
	fputc('\n', transformer_logfile);
}

#define DONT_LOG

void transformer_dump(void *str, int transformer_type, float *out_buffer, float *in_buffer, int sample)
{
	#ifndef DONT_LOG
	static int last_block_logged = -1;
	
	if (last_block_logged != blocks_recieved)
	{
		last_block_logged = blocks_recieved;
		fprintf(transformer_logfile, "NEW BLOCK: %d\n", blocks_recieved);
	}
	
	fprintf(transformer_logfile, "SAMPLE %04d: %s%f -> %s%f, ", sample, (in_buffer[sample] > 0) ? " " : "", in_buffer[sample], (out_buffer[sample] > 0) ? " " : "", out_buffer[sample]);

	switch (transformer_type)
	{
		case TRANSFORMER_DISTORTION:
			distortion_dump((tm_distortion_str*)str);
			break;
		
		default:
			fprintf(transformer_logfile, "UNKNOWN\n");
			break;
	}
	#endif
}
