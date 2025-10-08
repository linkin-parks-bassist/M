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

int init_transformer_default(tm_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	switch (type)
	{
		case TRANSFORMER_BUFFER:     return init_buffer_default(trans);
		case TRANSFORMER_AMPLIFIER:  return init_amplifier_default(trans);
		case TRANSFORMER_DISTORTION: return init_distortion_default(trans);
	}

	return NO_ERROR;
}
