#include "m_int.h"

static const char *unit_string_    = "";
static const char *unit_string_hz  = " Hz";
static const char *unit_string_ms  = " ms";
static const char *unit_string_db  = " dB";
static const char *unit_string_bpm = " bpm";

static const char *FNAME = "m_int_transformer_init.c";
int init_3_band_eq(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_3_BAND_EQ;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 0.0;
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

	param->value   = 0.0;
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

	param->value   = 0.0;
	param->max   = 18.0;
	param->min   = -18.0;
	param->name  = "High";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VSLIDER_TALL;

	return NO_ERROR;
}


int init_amplifier(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_AMPLIFIER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 0;
	param->max   = 12;
	param->min   = -12;
	param->name  = "Gain";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;


	m_setting *setting;

	setting = transformer_add_setting(trans);

	if (!setting)
		return ERR_ALLOC_FAIL;

	setting->id.setting_id = 0;

	setting->value   = 1;
	setting->max   = 255;
	setting->min   = 0;
	setting->name  = "Mode";
	setting->units = unit_string_;
	setting->group = -1;
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	setting->page = TRANSFORMER_SETTING_PAGE_SETTINGS;
	setting->n_options = 2;
	setting->options = m_alloc(sizeof(m_setting) * 2);
	if (!setting->options) return ERR_ALLOC_FAIL;

	setting->options[0].value = 0;
	setting->options[0].name = "Linear";

	setting->options[1].value = 1;
	setting->options[1].name = "dB";

	return NO_ERROR;
}


int init_band_pass_filter(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_BAND_PASS_FILTER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 1000.0;
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

	param->value   = 100.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Bandwidth";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_compressor(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_COMPRESSOR;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 2.0;
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

	param->value   = -5.0;
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

	param->value   = 30.0;
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

	param->value   = 30.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Release";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_delay(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DELAY;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = -6.0;
	param->max   = 0.0;
	param->min   = -12;
	param->name  = "Delay Gain";
	param->units = unit_string_db;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 0;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;


	m_setting *setting;

	setting = transformer_add_setting(trans);

	if (!setting)
		return ERR_ALLOC_FAIL;

	setting->id.setting_id = 0;

	setting->value   = 120;
	setting->max   = 1000;
	setting->min   = 1;
	setting->name  = "Tempo";
	setting->units = unit_string_;
	setting->group = 1;
	setting->widget_type = SETTING_WIDGET_FIELD;
	setting->page = TRANSFORMER_SETTING_PAGE_MAIN;
	setting->n_options = 0;
	setting->options = NULL;
	setting = transformer_add_setting(trans);

	if (!setting)
		return ERR_ALLOC_FAIL;

	setting->id.setting_id = 1;

	setting->value   = 4;
	setting->max   = 255;
	setting->min   = 0;
	setting->name  = "Note";
	setting->units = unit_string_;
	setting->group = 2;
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	setting->page = TRANSFORMER_SETTING_PAGE_MAIN;
	setting->n_options = 5;
	setting->options = m_alloc(sizeof(m_setting) * 5);
	if (!setting->options) return ERR_ALLOC_FAIL;

	setting->options[0].value = 1;
	setting->options[0].name = "Whole";

	setting->options[1].value = 2;
	setting->options[1].name = "Half";

	setting->options[2].value = 4;
	setting->options[2].name = "Quarter";

	setting->options[3].value = 8;
	setting->options[3].name = "Eighth";

	setting->options[4].value = 16;
	setting->options[4].name = "Sixteenth";

	return NO_ERROR;
}


int init_dirty_octave(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DIRTY_OCTAVE;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 5;
	param->max   = 10;
	param->min   = 0;
	param->name  = "Fuzz";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_distortion(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_DISTORTION;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 4.0;
	param->max   = 15;
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

	param->value   = 0.7;
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

	param->value   = 0.4;
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

	param->value   = 125;
	param->max   = 250;
	param->min   = 20;
	param->name  = "Bass Cutoff";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;


	m_setting *setting;

	setting = transformer_add_setting(trans);

	if (!setting)
		return ERR_ALLOC_FAIL;

	setting->id.setting_id = 0;

	setting->value   = 1;
	setting->max   = 255;
	setting->min   = 0;
	setting->name  = "Function";
	setting->units = unit_string_;
	setting->group = -1;
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	setting->page = TRANSFORMER_SETTING_PAGE_MAIN;
	setting->n_options = 4;
	setting->options = m_alloc(sizeof(m_setting) * 4);
	if (!setting->options) return ERR_ALLOC_FAIL;

	setting->options[0].value = 0;
	setting->options[0].name = "Clip";

	setting->options[1].value = 1;
	setting->options[1].name = "Tanh";

	setting->options[2].value = 2;
	setting->options[2].name = "Arctan";

	setting->options[3].value = 3;
	setting->options[3].name = "Fold";

	return NO_ERROR;
}


int init_envelope(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_ENVELOPE;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 200.0;
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

	param->value   = 2000.0;
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

	param->value   = 0.25;
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

	param->value   = 2.9;
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

	param->value   = 2.0;
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

	param->value   = 0.5;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Smoothness";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_flanger(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_FLANGER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 0.5;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Range";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->value   = 4.0;
	param->max   = 10.0;
	param->min   = 0.1;
	param->name  = "Depth";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 2;

	param->value   = 0.5;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Mix";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->value   = 120;
	param->max   = 300;
	param->min   = 30;
	param->name  = "Tempo";
	param->units = unit_string_bpm;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;


	m_setting *setting;

	setting = transformer_add_setting(trans);

	if (!setting)
		return ERR_ALLOC_FAIL;

	setting->id.setting_id = 0;

	setting->value   = 4;
	setting->max   = 255;
	setting->min   = 0;
	setting->name  = "Note";
	setting->units = unit_string_;
	setting->group = -1;
	setting->widget_type = SETTING_WIDGET_DROPDOWN;
	setting->page = TRANSFORMER_SETTING_PAGE_MAIN;
	setting->n_options = 5;
	setting->options = m_alloc(sizeof(m_setting) * 5);
	if (!setting->options) return ERR_ALLOC_FAIL;

	setting->options[0].value = 1;
	setting->options[0].name = "Whole";

	setting->options[1].value = 2;
	setting->options[1].name = "Half";

	setting->options[2].value = 4;
	setting->options[2].name = "Quarter";

	setting->options[3].value = 8;
	setting->options[3].name = "Eighth";

	setting->options[4].value = 16;
	setting->options[4].name = "Sixteenth";

	return NO_ERROR;
}


int init_high_pass_filter(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_HIGH_PASS_FILTER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 1000.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Cutoff Frequency";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_low_end_compressor(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_LOW_END_COMPRESSOR;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 2.0;
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

	param->value   = -12.0;
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

	param->value   = 10.0;
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

	param->value   = 200.0;
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

	param->value   = 2.0;
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

	param->value   = -8.0;
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

	param->value   = 20.0;
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

	param->value   = 200.0;
	param->max   = 250.0;
	param->min   = 0.01;
	param->name  = "Mid Release";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = 4;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_low_pass_filter(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_LOW_PASS_FILTER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 100.0;
	param->max   = 10000.0;
	param->min   = 1.0;
	param->name  = "Cutoff Frequency";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_noise_suppressor(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_NOISE_SUPPRESSOR;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = -50;
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

	param->value   = -30;
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

	param->value   = 1.0;
	param->max   = 20.0;
	param->min   = 0.0;
	param->name  = "Ratio";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_percussifier(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_PERCUSSIFIER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 120.0;
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

	param->value   = 16.0;
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

	param->value   = 3.0;
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

	param->value   = 1.5;
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

	param->value   = 2.9;
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

	param->value   = 6;
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

	param->value   = 100.0;
	param->max   = 700;
	param->min   = 0.0;
	param->name  = "Refractory Period";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_warbler(m_transformer *trans)
{
	if (!trans)
		return ERR_NULL_PTR;

	trans->type = TRANSFORMER_WARBLER;
	trans->view_page = NULL;

	m_parameter *param;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 0;

	param->value   = 440.0;
	param->max   = 1500.0;
	param->min   = 50.0;
	param->name  = "Center";
	param->units = unit_string_hz;
	param->scale = PARAMETER_SCALE_LOGARITHMIC;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 1;

	param->value   = 0.25;
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

	param->id.parameter_id = 2;

	param->value   = 100;
	param->max   = 0.5;
	param->min   = 200.0;
	param->name  = "Reactivity";
	param->units = unit_string_ms;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 3;

	param->value   = 2.0;
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

	param->id.parameter_id = 4;

	param->value   = 0.25;
	param->max   = 1.0;
	param->min   = 0.0;
	param->name  = "Min Rate";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	param = transformer_add_parameter(trans);

	if (!param)
		return ERR_ALLOC_FAIL;

	param->id.parameter_id = 5;

	param->value   = 0.5;
	param->max   = 3.0;
	param->min   = 1.0;
	param->name  = "Max Rate";
	param->units = unit_string_;
	param->scale = PARAMETER_SCALE_LINEAR;
	param->group = -1;
	param->widget_type = PARAM_WIDGET_VIRTUAL_POT;

	return NO_ERROR;
}


int init_transformer_of_type(m_transformer *trans, uint16_t type)
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
		case TRANSFORMER_DELAY:              return init_delay(trans);
		case TRANSFORMER_DIRTY_OCTAVE:       return init_dirty_octave(trans);
		case TRANSFORMER_DISTORTION:         return init_distortion(trans);
		case TRANSFORMER_ENVELOPE:           return init_envelope(trans);
		case TRANSFORMER_FLANGER:            return init_flanger(trans);
		case TRANSFORMER_HIGH_PASS_FILTER:   return init_high_pass_filter(trans);
		case TRANSFORMER_LOW_END_COMPRESSOR: return init_low_end_compressor(trans);
		case TRANSFORMER_LOW_PASS_FILTER:    return init_low_pass_filter(trans);
		case TRANSFORMER_NOISE_SUPPRESSOR:   return init_noise_suppressor(trans);
		case TRANSFORMER_PERCUSSIFIER:       return init_percussifier(trans);
		case TRANSFORMER_WARBLER:            return init_warbler(trans);
		default: return ERR_BAD_ARGS;
	}

	return NO_ERROR;
}
