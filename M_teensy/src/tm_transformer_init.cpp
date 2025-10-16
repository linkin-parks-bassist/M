// Code generated from config/transformer/*.yaml by codegen.py
#include "tm.h"

int init_amplifier(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_AMPLIFIER;

	trans->compute_transformer    = calc_amplifier;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_amplifier_str *str = (tm_amplifier_str*)malloc(sizeof(tm_amplifier_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = NULL;
	trans->free_struct = NULL;

	init_parameter(&str->gain, 1.0, 0.0, 2.0, 0.002, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->gain)) != NO_ERROR)
		return ret_val;

	return init_amplifier_str(str);
}

int init_compressor(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_COMPRESSOR;

	trans->compute_transformer    = calc_compressor;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 4);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_compressor_str *str = (tm_compressor_str*)malloc(sizeof(tm_compressor_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_compressor;
	trans->free_struct = NULL;

	init_parameter(&str->ratio, 2.0, 1.0, 10.0, 0.009000000000000001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->ratio)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->threshold, -5.0, 0.0, -30.0, 0.03, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->threshold)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->attack, 30.0, 0.01, 250.0, 0.24999000000000002, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->attack)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->release, 30.0, 0.01, 250.0, 0.24999000000000002, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->release)) != NO_ERROR)
		return ret_val;

	return init_compressor_str(str);
}

int init_low_pass_filter(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_LOW_PASS_FILTER;

	trans->compute_transformer    = calc_low_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_low_pass_filter_str *str = (tm_low_pass_filter_str*)malloc(sizeof(tm_low_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_low_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->cutoff_frequency, 100.0, 1.0, 10000.0, 0.9999, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->cutoff_frequency)) != NO_ERROR)
		return ret_val;

	return init_low_pass_filter_str(str);
}

int init_high_pass_filter(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_HIGH_PASS_FILTER;

	trans->compute_transformer    = calc_high_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_high_pass_filter_str *str = (tm_high_pass_filter_str*)malloc(sizeof(tm_high_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_high_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->cutoff_frequency, 1000.0, 1.0, 10000.0, 0.9999, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->cutoff_frequency)) != NO_ERROR)
		return ret_val;

	return init_high_pass_filter_str(str);
}

int init_band_pass_filter(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_BAND_PASS_FILTER;

	trans->compute_transformer    = calc_band_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 2);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_band_pass_filter_str *str = (tm_band_pass_filter_str*)malloc(sizeof(tm_band_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_band_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->center, 1000.0, 1.0, 10000.0, 0.9999, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->center)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->bandwidth, 100.0, 1.0, 10000.0, 0.9999, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->bandwidth)) != NO_ERROR)
		return ret_val;

	return init_band_pass_filter_str(str);
}

int init_dirty_octave(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_DIRTY_OCTAVE;

	trans->compute_transformer    = calc_dirty_octave;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_dirty_octave_str *str = (tm_dirty_octave_str*)malloc(sizeof(tm_dirty_octave_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = NULL;
	trans->free_struct = NULL;

	init_parameter(&str->fuzz, 5, 0, 10, 0.01, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->fuzz)) != NO_ERROR)
		return ret_val;

	return init_dirty_octave_str(str);
}

int init_noise_suppressor(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_NOISE_SUPPRESSOR;

	trans->compute_transformer    = calc_noise_suppressor;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 3);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_noise_suppressor_str *str = (tm_noise_suppressor_str*)malloc(sizeof(tm_noise_suppressor_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = NULL;
	trans->free_struct = NULL;

	init_parameter(&str->threshold, -50, -100, -10, 0.09, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->threshold)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->max_reduction, -30, 0, -100, 0.1, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->max_reduction)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->ratio, 1.0, 0.0, 20.0, 0.02, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->ratio)) != NO_ERROR)
		return ret_val;

	return init_noise_suppressor_str(str);
}

int init_percussifier(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_PERCUSSIFIER;

	trans->compute_transformer    = calc_percussifier;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 4);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_percussifier_str *str = (tm_percussifier_str*)malloc(sizeof(tm_percussifier_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_percussifier;
	trans->free_struct = NULL;

	init_parameter(&str->tempo, 120.0, 20, 300, 0.28, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->tempo)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->note, 16.0, 4.0, 32.0, 0.028, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->note)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->trigger_threshold, 3.0, 2.0, 4.0, 0.002, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->trigger_threshold)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->arm_threshold, 1.5, 1.0, 2.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->arm_threshold)) != NO_ERROR)
		return ret_val;

	return init_percussifier_str(str);
}

int init_distortion(tm_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = NO_ERROR;

	trans->type = TRANSFORMER_DISTORTION;

	trans->compute_transformer    = calc_distortion;
	trans->compute_transformer_nl = NULL;
	trans->bypass = 0;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	trans->n_inputs  = 1;
	trans->n_inputs  = 1;

	ret_val = transformer_init_parameter_array(trans, 8);
	if (ret_val != NO_ERROR)
		return ret_val;

	tm_distortion_str *str = (tm_distortion_str*)malloc(sizeof(tm_distortion_str));
	trans->data_struct = (void*)str;

	if (!str)
		return ERR_ALLOC_FAIL;

	trans->reconfigure = reconfigure_distortion;
	trans->free_struct = NULL;

	init_parameter(&str->gain, 4.0, 0.0, 5.0, 0.005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->gain)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->wet_mix, 0.7, 0.0, 1.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->wet_mix)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->high_mix, 0.55, 0.0, 1.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->high_mix)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->mid_mix, 0.8, 0.0, 1.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mid_mix)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->bass_mix, 0.3, 0.0, 1.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_mix)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->mid_cutoff, 2000.0, 1000.0, 10000.0, 0.9, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->mid_cutoff)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->bass_cutoff, 200.0, 1.0, 1000.0, 0.0999, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_cutoff)) != NO_ERROR)
		return ret_val;

	init_parameter(&str->ratio, 0.1, 0.0, 0.5, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->ratio)) != NO_ERROR)
		return ret_val;

	return init_distortion_str(str);
}

int init_transformer(tm_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	switch (type)
	{
		case TRANSFORMER_AMPLIFIER:        return init_amplifier(trans);
		case TRANSFORMER_COMPRESSOR:       return init_compressor(trans);
		case TRANSFORMER_LOW_PASS_FILTER:  return init_low_pass_filter(trans);
		case TRANSFORMER_HIGH_PASS_FILTER: return init_high_pass_filter(trans);
		case TRANSFORMER_BAND_PASS_FILTER: return init_band_pass_filter(trans);
		case TRANSFORMER_DIRTY_OCTAVE:     return init_dirty_octave(trans);
		case TRANSFORMER_NOISE_SUPPRESSOR: return init_noise_suppressor(trans);
		case TRANSFORMER_PERCUSSIFIER:     return init_percussifier(trans);
		case TRANSFORMER_DISTORTION:       return init_distortion(trans);
		default: return ERR_BAD_ARGS;
	}

	return NO_ERROR;
}
