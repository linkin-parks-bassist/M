// Code generated from transformer_config.yaml by codegen_teensy.py
#include "tm.h"

int init_buffer_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BUFFER;
	trans->compute_transformer = calc_buffer;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 0);

	trans->data_struct = NULL;

	return NO_ERROR;
}

int init_amplifier_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_AMPLIFIER;
	trans->compute_transformer = calc_amplifier;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 1);

	tm_amplifier_str *str = (tm_amplifier_str*)malloc(sizeof(tm_amplifier_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	param = &str->gain;
	init_parameter(param, 1.0, 0.0, 2.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	init_amplifier_struct_default(str);
	return NO_ERROR;
}

int init_mixer_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_MIXER;
	trans->compute_transformer = calc_mixer;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 2;
	trans->n_outputs = 2;

	transformer_init_parameter_array(trans, 1);

	tm_mixer_str *str = (tm_mixer_str*)malloc(sizeof(tm_mixer_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	param = &str->ratio;
	init_parameter(param, 0.5, 0.0, 1.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	init_mixer_struct_default(str);
	return NO_ERROR;
}

int init_biquad_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BIQUAD;
	trans->compute_transformer = calc_biquad;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 3);

	tm_biquad_str *str = (tm_biquad_str*)malloc(sizeof(tm_biquad_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	param = &str->cutoff;
	init_parameter(param, 440.0, 0.0, 5000.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->bandwidth;
	init_parameter(param, 200.0, 0.0, 1000.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->db_gain;
	init_parameter(param, 0.0, -3.0, 3.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	init_biquad_struct_default(str);
	return NO_ERROR;
}

int init_distortion_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DISTORTION;
	trans->compute_transformer = calc_distortion;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 8);

	tm_distortion_str *str = (tm_distortion_str*)malloc(sizeof(tm_distortion_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	param = &str->gain;
	init_parameter(param, 2.5, 0.0, 5.0, PARAMETER_UPDATE_INSTANT);
	transformer_add_parameter(trans, param);

	param = &str->wet_mix;
	init_parameter(param, 0.7, 0.0, 1.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->high_mix;
	init_parameter(param, 0.333, 0.0, 1.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->mid_mix;
	init_parameter(param, 0.333, 0.0, 1.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->bass_mix;
	init_parameter(param, 0.333, 0.0, 1.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->mid_cutoff;
	init_parameter(param, 1000.0, 1000.0, 5000.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->bass_cutoff;
	init_parameter(param, 100.0, 60.0, 1000.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->ratio;
	init_parameter(param, 0.1, 0.0, 0.5, PARAMETER_UPDATE_INSTANT);
	transformer_add_parameter(trans, param);

	init_distortion_struct_default(str);
	return NO_ERROR;
}

int init_compressor_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_COMPRESSOR;
	trans->compute_transformer = calc_compressor;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 4);

	tm_compressor_str *str = (tm_compressor_str*)malloc(sizeof(tm_compressor_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	param = &str->ratio;
	init_parameter(param, 2.0, 1.0, 10.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->threshold;
	init_parameter(param, -5.0, -30.0, 0.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->attack;
	init_parameter(param, 30.0, 0.01, 250.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	param = &str->release;
	init_parameter(param, 30.0, 0.01, 250.0, PARAMETER_UPDATE_MONOBLOCK_LINEAR);
	transformer_add_parameter(trans, param);

	init_compressor_struct_default(str);
	return NO_ERROR;
}

int init_waveshaper_default(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_WAVESHAPER;
	trans->compute_transformer = calc_waveshaper;

	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_outputs = 1;

	transformer_init_parameter_array(trans, 0);

	tm_waveshaper_str *str = (tm_waveshaper_str*)malloc(sizeof(tm_waveshaper_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	tm_parameter *param;
	init_waveshaper_struct_default(str);
	return NO_ERROR;
}

int init_transformer_of_type(tm_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	switch (type)
	{
		case TRANSFORMER_BUFFER:     return init_buffer_default(trans);
		case TRANSFORMER_AMPLIFIER:  return init_amplifier_default(trans);
		case TRANSFORMER_MIXER:      return init_mixer_default(trans);
		case TRANSFORMER_BIQUAD:     return init_biquad_default(trans);
		case TRANSFORMER_DISTORTION: return init_distortion_default(trans);
		case TRANSFORMER_COMPRESSOR: return init_compressor_default(trans);
		case TRANSFORMER_WAVESHAPER: return init_waveshaper_default(trans);
	}

	return NO_ERROR;
}
