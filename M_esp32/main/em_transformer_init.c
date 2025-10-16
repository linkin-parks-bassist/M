#include "em.h"

static const char *unit_string_ = "";
static const char *unit_string_hz = " Hz";
static const char *unit_string_ms = " ms";
static const char *unit_string_db = " dB";

int init_amplifier(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_AMPLIFIER;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 1.0;
	param->max   = 2.0;
	param->min   = 0.0;
	param->name  = "Gain";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_compressor(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_COMPRESSOR;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 2.0;
	param->max   = 10.0;
	param->min   = 1.0;
	param->name  = "Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = -5.0;
	param->max   = -30.0;
	param->min   = 0.0;
	param->name  = "Threshold";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 30.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Attack";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 30.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Release";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_low_pass_filter(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_LOW_PASS_FILTER;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 100.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Cutoff Frequency";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_high_pass_filter(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_HIGH_PASS_FILTER;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 1000.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Cutoff Frequency";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_band_pass_filter(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BAND_PASS_FILTER;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 1000.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Center";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = 100.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Bandwidth";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_dirty_octave(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DIRTY_OCTAVE;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 5;
	param->max   = 10;
	param->min   = 0;
	param->name  = "Fuzz";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_noise_suppressor(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_NOISE_SUPPRESSOR;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = -50;
	param->max   = -10;
	param->min   = -100;
	param->name  = "Threshold";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = -30;
	param->max   = -100;
	param->min   = 0;
	param->name  = "Max Reduction";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 1.0;
	param->max   = 20.0;
	param->min   = 0.0;
	param->name  = "Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_percussifier(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_PERCUSSIFIER;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 120.0;
	param->max   = 300;
	param->min   = 20;
	param->name  = "Tempo";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = 16.0;
	param->max   = 32.0;
	param->min   = 4.0;
	param->name  = "Note";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 3.0;
	param->max   = 4.0;
	param->min   = 2.0;
	param->name  = "Trigger Threshold";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 1.5;
	param->max   = 2.0;
	param->min   = 1.0;
	param->name  = "Arm Threshold";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_distortion(em_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DISTORTION;
	trans->view_page = NULL;

	em_parameter *param;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 4.0;
	param->max   = 5.0;
	param->min   = 0.0;
	param->name  = "Gain";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = 0.7;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Wet Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 0.55;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "High Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 0.8;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Mid Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 4;

	param->val   = 0.3;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Bass Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 5;

	param->val   = 2000.0;
	param->max   = 10000.0;
	param->min   = 1000.0;
	param->name  = "Mid Cutoff";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 6;

	param->val   = 200.0;
	param->max   = 1000.0;
	param->min   = 1.0;
	param->name  = "Bass Cutoff";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter_rp(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 7;

	param->val   = 0.1;
	param->max   = 0.5;
	param->min   = 0.0;
	param->name  = "Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_HSLIDER;

	return NO_ERROR;
}


int init_transformer_of_type(em_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = init_transformer(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;
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
