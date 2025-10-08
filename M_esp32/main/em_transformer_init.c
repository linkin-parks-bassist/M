// Code generated from transformer_config.yaml by codegen_esp32.py
#include "em.h"

int init_transformer_buffer(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BUFFER;
	return NO_ERROR;
}


int init_transformer_amplifier(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_AMPLIFIER;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 0;
	init_parameter(param, "Gain", 1.0, 0.0, 2.0);

	return NO_ERROR;
}


int init_transformer_mixer(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_MIXER;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 0;
	init_parameter(param, "Ratio", 0.5, 0.0, 1.0);

	return NO_ERROR;
}


int init_transformer_biquad(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BIQUAD;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 0;
	init_parameter(param, "Cutoff", 440.0, 0.0, 5000.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 1;
	init_parameter(param, "Bandwidth", 200.0, 0.0, 1000.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 2;
	init_parameter(param, "Gain (dB)", 0.0, -3.0, 3.0);

	return NO_ERROR;
}


int init_transformer_distortion(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DISTORTION;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 0;
	init_parameter(param, "Gain", 2.5, 0.0, 5.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 1;
	init_parameter(param, "Wet Mix", 0.7, 0.0, 1.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 2;
	init_parameter(param, "High Mix", 0.333, 0.0, 1.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 3;
	init_parameter(param, "Mid Mix", 0.333, 0.0, 1.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 4;
	init_parameter(param, "Bass Mix", 0.333, 0.0, 1.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 5;
	init_parameter(param, "Mid Cutoff", 1000.0, 1000.0, 5000.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 6;
	init_parameter(param, "Bass Cutoff", 100.0, 60.0, 1000.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 7;
	init_parameter(param, "Ratio", 0.1, 0.0, 0.5);

	return NO_ERROR;
}


int init_transformer_compressor(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_COMPRESSOR;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 0;
	init_parameter(param, "Ratio", 2.0, 1.0, 10.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 1;
	init_parameter(param, "Threshold", -5.0, -30.0, 0.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 2;
	init_parameter(param, "Attack", 30.0, 0.01, 250.0);

	param = transformer_add_parameter_rp(trans);
	param->id.parameter_id = 3;
	init_parameter(param, "Release", 30.0, 0.01, 250.0);

	return NO_ERROR;
}


int init_transformer_waveshaper(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_WAVESHAPER;
	return NO_ERROR;
}


int init_transformer_of_type(em_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = init_transformer(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;

	em_parameter *param;
	switch (type)
	{
		case TRANSFORMER_BUFFER:     return init_transformer_buffer(trans);
		case TRANSFORMER_AMPLIFIER:  return init_transformer_amplifier(trans);
		case TRANSFORMER_MIXER:      return init_transformer_mixer(trans);
		case TRANSFORMER_BIQUAD:     return init_transformer_biquad(trans);
		case TRANSFORMER_DISTORTION: return init_transformer_distortion(trans);
		case TRANSFORMER_COMPRESSOR: return init_transformer_compressor(trans);
		case TRANSFORMER_WAVESHAPER: return init_transformer_waveshaper(trans);
	}

	return NO_ERROR;
}
