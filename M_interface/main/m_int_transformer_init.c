#include "m_int.h"

static const char *unit_string_ = "";
static const char *unit_string_hz = " Hz";
static const char *unit_string_ms = " ms";
static const char *unit_string_db = " dB";

static const char *FNAME = "m_int_transformer_init.c";
int init_3_band_eq(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_3_BAND_EQ;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 0.0;
	param->max   = 18.0;
	param->min   = -18.0;
	param->name  = "Low";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER_TALL;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = 0.0;
	param->max   = 18.0;
	param->min   = -18.0;
	param->name  = "Mid";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER_TALL;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 0.0;
	param->max   = 18.0;
	param->min   = -18.0;
	param->name  = "High";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER_TALL;

	return NO_ERROR;
}


int init_amplifier(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_AMPLIFIER;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 0;
	param->max   = 12;
	param->min   = -12;
	param->name  = "Gain";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_band_pass_filter(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BAND_PASS_FILTER;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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


int init_compressor(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_COMPRESSOR;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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


int init_dirty_octave(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DIRTY_OCTAVE;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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


int init_distortion(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DISTORTION;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 4.0;
	param->max   = 10;
	param->min   = 0.0;
	param->name  = "Gain";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 0.4;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Bass Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 125;
	param->max   = 250;
	param->min   = 20;
	param->name  = "Bass Cutoff";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_envelope(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_ENVELOPE;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 200.0;
	param->max   = 500.0;
	param->min   = 50.0;
	param->name  = "Min Center";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = 2000.0;
	param->max   = 5000.0;
	param->min   = 200.0;
	param->name  = "Max Center";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 0.25;
	param->max   = 1.0;
	param->min   = 0.1;
	param->name  = "Width";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 2.9;
	param->max   = 0.5;
	param->min   = 200.0;
	param->name  = "Speed";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 4;

	param->val   = 2.0;
	param->max   = 10.0;
	param->min   = 0.1;
	param->name  = "Sensitivity";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 5;

	param->val   = 0.5;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Smoothness";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_high_pass_filter(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_HIGH_PASS_FILTER;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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


int init_low_end_compressor(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_LOW_END_COMPRESSOR;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->val   = 2.0;
	param->max   = 10.0;
	param->min   = 1.0;
	param->name  = "Bass Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->val   = -12.0;
	param->max   = -30.0;
	param->min   = 0.0;
	param->name  = "Bass Threshold";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 10.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Bass Attack";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 2;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 200.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Bass Release";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 2;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 4;

	param->val   = 2.0;
	param->max   = 10.0;
	param->min   = 1.0;
	param->name  = "Mid Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 3;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 5;

	param->val   = -8.0;
	param->max   = -30.0;
	param->min   = 0.0;
	param->name  = "Mid Threshold";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 3;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 6;

	param->val   = 20.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Mid Attack";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 4;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 7;

	param->val   = 200.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Mid Release";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 4;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_low_pass_filter(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_LOW_PASS_FILTER;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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


int init_noise_suppressor(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_NOISE_SUPPRESSOR;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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


int init_percussifier(m_int_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_PERCUSSIFIER;
	trans->view_page = NULL;

	m_int_parameter *param;

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

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

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->val   = 3.0;
	param->max   = 4.0;
	param->min   = 0.0;
	param->name  = "Trigger Threshold";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->val   = 1.5;
	param->max   = 2.0;
	param->min   = 0.0;
	param->name  = "Arm Threshold";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 4;

	param->val   = 2.9;
	param->max   = 10.0;
	param->min   = 0.5;
	param->name  = "Fade In";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 5;

	param->val   = 6;
	param->max   = 10.0;
	param->min   = 0.5;
	param->name  = "Fade Out";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 6;

	param->val   = 100.0;
	param->max   = 700;
	param->min   = 0.0;
	param->name  = "Refractory Period";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_transformer_of_type(m_int_transformer *trans, uint16_t type)
{
	if (!trans)
		return ERR_NULL_PTR;

	int ret_val = init_transformer(trans);
	
	if (ret_val != NO_ERROR)
		return ret_val;
	switch (type)
	{
		case TRANSFORMER_3_BAND_EQ:          return init_3_band_eq(trans);
		case TRANSFORMER_AMPLIFIER:          return init_amplifier(trans);
		case TRANSFORMER_BAND_PASS_FILTER:   return init_band_pass_filter(trans);
		case TRANSFORMER_COMPRESSOR:         return init_compressor(trans);
		case TRANSFORMER_DIRTY_OCTAVE:       return init_dirty_octave(trans);
		case TRANSFORMER_DISTORTION:         return init_distortion(trans);
		case TRANSFORMER_ENVELOPE:           return init_envelope(trans);
		case TRANSFORMER_HIGH_PASS_FILTER:   return init_high_pass_filter(trans);
		case TRANSFORMER_LOW_END_COMPRESSOR: return init_low_end_compressor(trans);
		case TRANSFORMER_LOW_PASS_FILTER:    return init_low_pass_filter(trans);
		case TRANSFORMER_NOISE_SUPPRESSOR:   return init_noise_suppressor(trans);
		case TRANSFORMER_PERCUSSIFIER:       return init_percussifier(trans);
		default: return ERR_BAD_ARGS;
	}

	return NO_ERROR;
}
