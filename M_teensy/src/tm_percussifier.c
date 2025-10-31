#include "tm.h"

static const char *FNAME = "tm_percussifier.c";
int reconfigure_percussifier(void *data_struct)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_percussifier_str *str = (tm_percussifier_str*)data_struct;
	
	// The number of samples in a note'th note is
	// samples per beat * 4 / note (as, a quater note (note = 4.0), is a single beat)
	// samples per beat = samples (per second * seconds) per beat = (samples per second) * (seconds per beat)
	// 					= samples per second * (seconds per minute * minutes per beat)
	// 					= samples per second * (seconds per minute * (1 / beats per minute))
	// 					= samples per second * (seconds per minute / beats per minute)
	//
	// so the number of samples in a note'th note is
	//
	// 			samples = samples per second * (seconds per minute / beats per minute) * (4 / note)
	
	str->hold_samples = AUDIO_SAMPLE_RATE * (60.0 / str->tempo.value) * (4.0 / str->note.value);
	
	str->refractory_samples = MS_TO_SAMPLES(str->refractory_period.value);
	str->fade_in_samples = MS_TO_SAMPLES(str->fade_in.value);
	str->fade_alpha = expf(-7.0/MS_TO_SAMPLES(str->fade_out.value));
	
	RETURN_ERR_CODE(NO_ERROR);
}

int calc_percussifier(void *data_struct, float *dest, float *src, int n_samples)
{
	FUNCTION_START();

	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	tm_percussifier_str *str = (tm_percussifier_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;

	float rms_short = str->rms_short;
	float rms_long  = str->rms_long;
	float g;
	
	for (int i = 0; i < n_samples; i++)
	{
		rms_short = (1.0 - str->alpha_short) * rms_short + (str->alpha_short) * fabsf(in_buffer[i]);
		rms_long  = (1.0 - str->alpha_long)  * rms_long  + (str->alpha_long)  * fabsf(in_buffer[i]);
		
		/*if (i == 127 && str->r % 64 == 0)
		{
			tm_printf("Percussifier: rms_short = %f, rms_long = %f, (rms_short / (rms_long + 1e-12f)) = %f, state = %s\n",
				rms_short, rms_long, (rms_short / (rms_long + 1e-12f)),
				(str->state == PERCUSSIFIER_MUTE) ? "PERCUSSIFIER_MUTE" : ((str->state == PERCUSSIFIER_FADE_IN) ? "PERCUSSIFIER_FADE_IN" :
				((str->state == PERCUSSIFIER_HOLD) ? "PERCUSSIFIER_HOLD" : "PERCUSSIFIER_FADE_OUT")));
		}*/
		
		out_buffer[i] = str->gain * in_buffer[i];
		str->timer++;
			
		switch (str->state)
		{
			case PERCUSSIFIER_MUTE:
				if ((rms_short / (rms_long + 1e-12f)) > str->trigger_threshold.value)
				{
					str->state = PERCUSSIFIER_FADE_IN;
					str->timer = 0;
				}
				break;
			
			case PERCUSSIFIER_FADE_IN:
				if (str->timer >= str->fade_in_samples)
				{
					str->gain = 1.0;
					str->state = PERCUSSIFIER_HOLD;
				}
				else
				{
					str->gain = 0.5 * (1 - cosf(PI * ((float)str->timer / (float)str->fade_in_samples)));
				}
				
				break;
			
			case PERCUSSIFIER_HOLD:
				if (str->timer >= str->hold_samples)
				{
					str->state = PERCUSSIFIER_FADE_OUT;
					str->timer = 0;
				}
				break;
			
			case PERCUSSIFIER_FADE_OUT:
				str->gain *= str->fade_alpha;
				
				if (str->gain < 0.001)
				{
					str->gain = 0.0;
					str->state = PERCUSSIFIER_REFRACTORY;
					str->timer = 0;
				}
				break;
			
			case PERCUSSIFIER_REFRACTORY:
				if (str->timer > str->refractory_samples && (rms_short / (rms_long + 1e-12f)) < str->arm_threshold.value)
				{
					str->state = PERCUSSIFIER_MUTE;
				}
				break;
				
			default:
				str->state = PERCUSSIFIER_MUTE;
				out_buffer[i] = 0.0;
				break;
		}
	}
	
	str->rms_short = rms_short;
	str->rms_long  = rms_long;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int init_percussifier_str(tm_percussifier_str *str)
{
	FUNCTION_START();

	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->rms_short = 0.0;
	str->rms_long  = 0.0;
	
	str->alpha_short = 0.003;
	str->alpha_long  = 0.0005;
	
	str->timer = 0;
	str->gain = 0.0;
	
	str->fade_alpha 	 	= expf(-7.0/512.0);
	str->refractory_samples = 5000;
	
	str->fade_in_samples = 128;
	
	str->state = PERCUSSIFIER_MUTE;
	
	RETURN_ERR_CODE(NO_ERROR);
}
