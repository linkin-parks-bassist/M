#include "m_eng.h"
static const char *FNAME = "m_eng_flanger.c";

int init_flanger_str(m_eng_flanger_str *str)
{
	if (!str)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	str->block_memory = NULL;
	str->num_blocks   = 0;
	str->block_index  = 0;
	
	reconfigure_flanger(str);
	
	str->t = 0;
	str->block_position = 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int reconfigure_flanger(void *data_struct)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_flanger_str *str = (m_eng_flanger_str*)data_struct;
	
	str->d = MS_TO_SAMPLES(str->depth.value);
	str->r = binary_min(str->range.value * str->d, str->d - 1);
	float lfo_freq = (str->tempo.value / 60.0f) / str->note.value;
	str->s = 2 * PI * lfo_freq;
	str->period = 1.0f / lfo_freq;
	
	str->wet_mix = sinf(0.5f * PI * str->mix.value);
	str->dry_mix = cosf(0.5f * PI * str->mix.value);
	
	float max_history = ceilf(str->d + str->r);
	float **new_array = NULL;
	
	int blocks_needed = ceilf(max_history / AUDIO_BLOCK_SAMPLES);
	
	if (str->block_memory && blocks_needed == str->num_blocks)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	if (!str->block_memory)
	{
		str->block_memory = malloc(sizeof(float*) * blocks_needed);
		
		for (int i = 0; i < blocks_needed; i++)
			str->block_memory[i] = NULL;
		
		for (int i = 0; i < blocks_needed; i++)
		{
			if (!(str->block_memory[i] = allocate_buffer()))
				goto flanger_alloc_fail;
			
			for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
				str->block_memory[i][j] = 0.0f;
		}
		
		str->block_index = 0;
		str->num_blocks  = blocks_needed;
	}
	else if (str->num_blocks < blocks_needed)
	{
		new_array = malloc(blocks_needed * sizeof(float*));
		
		if (!new_array)
			goto flanger_alloc_fail;
		
		for (int i = 0; i < str->num_blocks; i++)
			new_array[i] = str->block_memory[(str->block_index + 1 + i) % str->num_blocks];
		
		for (int i = str->num_blocks; i < blocks_needed; i++)
			new_array[i] = NULL;
		
		for (int i = str->num_blocks; i < blocks_needed; i++)
		{
			if (!(new_array[i] = allocate_buffer()))
				goto flanger_alloc_fail;
			
			for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
				new_array[i][j] = 0.0f;
		}
		
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
			new_array[0][i] *= 1.0 - sqr(cosf(PI * (float)i / (float)(2 * AUDIO_BLOCK_SAMPLES)));
		
		free(str->block_memory);
		str->block_memory = new_array;
		str->block_index = str->num_blocks - 1;
		str->num_blocks = blocks_needed;
	}
	
	RETURN_ERR_CODE(NO_ERROR);

flanger_alloc_fail:
	
	if (new_array)
	{
		for (int i = 0; i < blocks_needed; i++)
		{
			if (new_array[i])
				release_buffer(new_array[i]);
		}
		
		free(new_array);
		str->block_memory = NULL;
		str->num_blocks = 0;
	}
	
	RETURN_ERR_CODE(ERR_ALLOC_FAIL);
}

int calc_flanger(void *data_struct, float *dest, float *src, int n_samples)
{
	if (!data_struct)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	m_eng_flanger_str *str = (m_eng_flanger_str*)data_struct;
	
	float *in_buffer  =  src ? src  : zero_buffer;
	float *out_buffer = dest ? dest : sink_buffer;
	
	float mix_sample;
	
	int block_difference;
	
	float delay;
	float sample_pos;
	float fractional_pos;
	
	int early_sample_index;
	int late_sample_index;
	
	int early_sample_block_index;
	int late_sample_block_index;
	
	float early_sample;
	float late_sample;

	for (int i = 0; i < n_samples; i++)
	{
		if (str->block_position >= AUDIO_BLOCK_SAMPLES)
		{
			str->block_index = (str->block_index + 1) % str->num_blocks;
			str->block_position = str->block_position % AUDIO_BLOCK_SAMPLES;
		}
		
		str->block_memory[str->block_index][str->block_position] = in_buffer[i];
		
		delay = str->d + str->r * cosf(str->s * str->t);

		sample_pos = (float)str->block_position - delay;
		fractional_pos = sample_pos - floorf(sample_pos);
		
		block_difference = 0;
		while (sample_pos < 0)
		{
			sample_pos += AUDIO_BLOCK_SAMPLES;
			block_difference++;
		}
		
		early_sample_block_index = str->block_index - block_difference;
		
		while (early_sample_block_index < 0)
			early_sample_block_index += str->num_blocks;
		
		early_sample_index = (int)floorf(sample_pos);
		late_sample_index  = early_sample_index + 1;
		
		if (late_sample_index >= AUDIO_BLOCK_SAMPLES)
		{
			late_sample_index = late_sample_index % AUDIO_BLOCK_SAMPLES;
			late_sample_block_index = (early_sample_block_index + 1) % str->num_blocks;
		}
		else
		{
			late_sample_block_index = early_sample_block_index;
		}
		
		early_sample = str->block_memory[early_sample_block_index][early_sample_index];
		late_sample  = str->block_memory[late_sample_block_index ][late_sample_index ];
		
		mix_sample = (1.0 - fractional_pos) * early_sample + fractional_pos * late_sample;
		
		out_buffer[i] = str->mix.value * mix_sample + (1.0 - str->mix.value) * in_buffer[i];
		
		str->t += SAMPLE_FREQUENCY;
		
		while (str->t > str->period)
			str->t -= str->period;
		
		str->block_position++;
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}
