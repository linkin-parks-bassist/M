#include "m_eng_sim.h"
#include <sndfile.h>
#include <time.h>

#define SIMULATOR_INPUT_FILE "simulator/sample.wav"
#define SIMULATOR_AUDIO_OUTPUT_FNAME "simulator/sim_output.wav"

IMPLEMENT_LINKED_LIST(m_message_timed);

m_message_timed_ll *message_list = NULL;

m_response teensy_i2c_response;
uint8_t simulated_i2c_send_buffer[M_MESSAGE_MAX_TRANSFER_LEN];

SF_INFO sfinfo_out;
SNDFILE *outfile = NULL;

int ask_for_response = 0;

void run_teensy_init()
{
	m_printf("Initialising memory pools... ");
	init_mem_pools();
	m_printf("done.\n");
	
	m_printf("Initialising context struct... ");
	init_m_eng_context(&global_cxt);
	m_printf("done.\n");
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

void add_message_to_queue(m_message msg, int block_no)
{
	m_message_timed tmsg;
	
	tmsg.msg = msg;
	tmsg.block_no = block_no;
	
	message_list = m_message_timed_ll_append(message_list, tmsg);
}

void generam_response_queue()
{
	add_message_to_queue(create_m_message(M_MESSAGE_CREATE_PROFILE,     "", 0), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_APPEND_TRANSFORMER, "ss", 1, TRANSFORMER_DISTORTION), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 0, 0.0), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 1, 0.0), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 2, 0.0), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 3, 0.797844), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 4, 0.300000), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 5, 2000.000000), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 6, 200.000000), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE,    "sssf", 1, 0, 7, 0.100000), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_APPEND_TRANSFORMER,    "ss", 0, TRANSFORMER_ENVELOPE), 128);
	add_message_to_queue(create_m_message(M_MESSAGE_APPEND_TRANSFORMER,    "ss", 0, TRANSFORMER_DISTORTION), 256);
	add_message_to_queue(create_m_message(M_MESSAGE_REMOVE_TRANSFORMER,    "sss", 0, 0, 1), 312);
}

m_message generate_random_msg()
{
	m_message msg;
	
	msg.type = rand() % M_MESSAGE_TYPE_MAX;
	
	int len = et_message_data_length(msg);
	
	for (int i = 0; i < len; i++)
		msg.data[i] = rand() % ((rand() % 32) + 1);
	
	return msg;
}

#define PROB_BIG 100000

void generate_stress_test_msg_queue(int n, int blocks)
{
	srand(time(0));
	
	int prob = PROB_BIG * ((float)n / (float)blocks);
	
	printf("prob = %d / %d\n", prob, PROB_BIG);
	
	m_message msg;
	
	int m = 0;
	for (int i = 0; i < blocks; i++)
	{
		if ((rand() % PROB_BIG) <= prob)
		{
			msg = generate_random_msg();
			
			printf("Send message %s at block %d\n", m_message_code_to_string(msg.type), i);
			
			add_message_to_queue(msg, i);
			m++;
		}
	}
	
	printf("... for a total of %d messages.\n", m);
}

int m_sim_send_m_message(m_message msg)
{
	printf("Sending message to simulated teensy...\n");
	int len = encode_m_message(simulated_i2c_send_buffer, msg);
	
	i2c_receive_isr(len);
	
	ask_for_response = 1;
	
	return NO_ERROR;
}

int main(int argc, char **argv)
{
	sfinfo_out.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
	sfinfo_out.channels = 1;
	sfinfo_out.samplerate = 44100;
	
	outfile = sf_open(SIMULATOR_AUDIO_OUTPUT_FNAME, SFM_WRITE, &sfinfo_out);
	
	if (!outfile)
	{
		printf("Failed to open %s\n", SIMULATOR_AUDIO_OUTPUT_FNAME);
		abort();
	}
	
	int n_blocks = 1 << 12;
	
	run_teensy_init();
	
	add_message_to_queue(create_m_message(M_MESSAGE_SET_PARAM_VALUE, "sssf", 0xFFFF, 0, 0, 0.0f), 0);
	add_message_to_queue(create_m_message(M_MESSAGE_APPEND_TRANSFORMER, "sssf", 0, TRANSFORMER_FLANGER), 1);
	
	//generate_stress_test_msg_queue(500, n_blocks);
	
	m_message_timed_ll *current = message_list;
	m_message_timed_ll *next = next = current ? current->next : NULL;
	
	for (int i = 0; i < n_blocks; i++)
	{
		if (current)
		{
			if (i >= current->data.block_no)
			{
				m_sim_send_m_message(current->data.msg);
				m_free(current);
				current = next;
				next = current ? current->next : NULL;
			}
		}
		
		run_teensy_loop();
	}
	
	print_context_info(&global_cxt, -1);
	print_memory_report();
	sf_close(outfile);
	
	return 0;
}

typedef struct
{
	SNDFILE *sim_sf;
	SF_INFO sim_info;
	sf_count_t sim_pos;
} m_sim_sound_file;

int m_sim_sound_file_init(m_sim_sound_file *fstruct)
{
	if (!fstruct)
		return ERR_NULL_PTR;
	
	fstruct->sim_sf = NULL;
    fstruct->sim_pos = 0;
}


int m_sim_close_sound_file(m_sim_sound_file *fstruct)
{
	if (!fstruct)
		return ERR_NULL_PTR;
	
    if (fstruct->sim_sf)
        sf_close(fstruct->sim_sf);

    fstruct->sim_sf = NULL;
    fstruct->sim_pos = 0;
    
    return NO_ERROR;
}

int m_sim_open_sound_file(const char *path, m_sim_sound_file *fstruct)
{
	if (!fstruct)
		return ERR_NULL_PTR;
		
    if (fstruct->sim_sf)
        m_sim_close_sound_file(fstruct);

    fstruct->sim_pos = 0;

    fstruct->sim_sf = sf_open(path, SFM_READ, &fstruct->sim_info);
    
    if (!fstruct->sim_sf)
    {
        m_printf("sim_open: sf_open failed: %s\n", sf_strerror(NULL));
        return ERR_FOPEN_FAIL;
    }

    return NO_ERROR;;
}

sf_count_t m_sim_read_sound_file_mono(m_sim_sound_file *fstruct, float *dest, sf_count_t n)
{
    if (!fstruct)
        return 0;

	if(!fstruct->sim_sf)
		return 0;
	
    sf_count_t read = sf_read_float(fstruct->sim_sf, dest, n);

    if (read < n)
    {
        for (sf_count_t i = read; i < n; i++)
            dest[i] = 0.0f;
    }

    return n;
}

int m_sim_restart_sound_file(m_sim_sound_file *fstruct)
{
	if (!fstruct)
		return ERR_NULL_PTR;
	
	if(!fstruct->sim_sf)
		return ERR_BAD_ARGS;
	
	sf_seek(fstruct->sim_sf, 0, SEEK_SET);
	
	return NO_ERROR;
}

int m_sim_get_input_block(float *dest)
{
	static m_sim_sound_file input_file;
	static int input_file_opened = 0;
	static uint32_t n_samples = 0;
	
	if (!input_file_opened)
	{
		m_sim_sound_file_init(&input_file);
		
		if (m_sim_open_sound_file(SIMULATOR_INPUT_FILE, &input_file) != NO_ERROR)
		{
			printf("Failed to open %s\n", SIMULATOR_INPUT_FILE);
			abort();
		}
		else
		{
			printf("Sucessfully opened %s\n", SIMULATOR_INPUT_FILE);
		}
		
		input_file_opened = 1;
	}
	
	sf_count_t samples = m_sim_read_sound_file_mono(&input_file, dest, AUDIO_BLOCK_SAMPLES);
	
	if (samples < AUDIO_BLOCK_SAMPLES)
	{
		m_sim_restart_sound_file(&input_file);
	}
	
	return NO_ERROR;
}

uint32_t blocks_recieved = 0;
uint32_t samples_recieved = 0;

int m_sim_get_output_block(float *buffer)
{
	blocks_recieved++;
	sf_writef_float(outfile, buffer, AUDIO_BLOCK_SAMPLES);
	return NO_ERROR;
}
