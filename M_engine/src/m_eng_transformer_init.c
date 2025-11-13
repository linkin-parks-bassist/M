// Code generated from config/transformer/*.yaml by codegen.py
#include "m_eng.h"

static const char *FNAME = "m_eng_transformer_init.c";

int init_3_band_eq(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_3_BAND_EQ;

	trans->compute_transformer    = calc_3_band_eq;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 3);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_3_band_eq_str *str = (m_eng_3_band_eq_str*)malloc(sizeof(m_eng_3_band_eq_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_3_band_eq;
	trans->free_struct = NULL;

	init_parameter(&str->low, 0.0, -18.0, 18.0, 0.018, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->low)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mid, 0.0, -18.0, 18.0, 0.018, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mid)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->high, 0.0, -18.0, 18.0, 0.018, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->high)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_3_band_eq_str);
	ret_val = init_3_band_eq_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_amplifier(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_AMPLIFIER;

	trans->compute_transformer    = calc_amplifier;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_amplifier_str *str = (m_eng_amplifier_str*)malloc(sizeof(m_eng_amplifier_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_amplifier;
	trans->free_struct = NULL;

	init_parameter(&str->gain, 0, -12, 12, 0.012, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->gain)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_setting(&str->mode, 1);
	if ((ret_val = transformer_add_setting(trans, &str->mode)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_amplifier_str);
	ret_val = init_amplifier_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_band_pass_filter(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_BAND_PASS_FILTER;

	trans->compute_transformer    = calc_band_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 2);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_band_pass_filter_str *str = (m_eng_band_pass_filter_str*)malloc(sizeof(m_eng_band_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_band_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->center, 1000.0, 1.0, 10000.0, 0.49995, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->center)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->bandwidth, 100.0, 1.0, 10000.0, 0.49995, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->bandwidth)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_band_pass_filter_str);
	ret_val = init_band_pass_filter_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_compressor(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_COMPRESSOR;

	trans->compute_transformer    = calc_compressor;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 4);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_compressor_str *str = (m_eng_compressor_str*)malloc(sizeof(m_eng_compressor_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_compressor;
	trans->free_struct = NULL;

	init_parameter(&str->ratio, 2.0, 1.0, 10.0, 0.0045, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->ratio)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->threshold, -5.0, 0.0, -30.0, 0.015, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->attack, 30.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->attack)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->release, 30.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->release)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_compressor_str);
	ret_val = init_compressor_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_dirty_octave(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_DIRTY_OCTAVE;

	trans->compute_transformer    = calc_dirty_octave;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_dirty_octave_str *str = (m_eng_dirty_octave_str*)malloc(sizeof(m_eng_dirty_octave_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = NULL;
	trans->free_struct = NULL;

	init_parameter(&str->fuzz, 5, 0, 10, 0.005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->fuzz)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_dirty_octave_str);
	ret_val = init_dirty_octave_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_distortion(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_DISTORTION;

	trans->compute_transformer    = calc_distortion;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 4);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_distortion_str *str = (m_eng_distortion_str*)malloc(sizeof(m_eng_distortion_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_distortion;
	trans->free_struct = NULL;

	init_parameter(&str->dist.coefficient, 4.0, 0.0, 10, 0.005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->dist.coefficient)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->wet_mix, 0.7, 0.0, 1.0, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->wet_mix)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->bass_mix, 0.4, 0.0, 1.0, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_mix)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->low_pass.cutoff_frequency, 125, 20, 250, 0.0115, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->low_pass.cutoff_frequency)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_distortion_str);
	ret_val = init_distortion_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_envelope(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_ENVELOPE;

	trans->compute_transformer    = calc_envelope;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 6);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_envelope_str *str = (m_eng_envelope_str*)malloc(sizeof(m_eng_envelope_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_envelope;
	trans->free_struct = NULL;

	init_parameter(&str->min_center, 200.0, 50.0, 500.0, 0.0225, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->min_center)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->max_center, 2000.0, 200.0, 5000.0, 0.24, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->max_center)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->width, 0.25, 0.1, 1.0, 0.00045, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->width)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->speed, 2.9, 200.0, 0.5, 0.09975, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->speed)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->sensitivity, 2.0, 0.1, 10.0, 0.00495, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->sensitivity)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->smoothness, 0.5, 0.0, 1.0, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->smoothness)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_envelope_str);
	ret_val = init_envelope_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_flanger(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_FLANGER;

	trans->compute_transformer    = calc_flanger;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 4);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_flanger_str *str = (m_eng_flanger_str*)malloc(sizeof(m_eng_flanger_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_flanger;
	trans->free_struct = NULL;

	init_parameter(&str->range, 0.5, 0.0, 1.0, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->range)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->depth, 4.0, 0.1, 10.0, 0.00495, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->depth)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mix, 0.5, 0.0, 1.0, 0.0005, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mix)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->tempo, 120, 30, 300, 0.135, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->tempo)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_setting(&str->note, 4);
	if ((ret_val = transformer_add_setting(trans, &str->note)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_flanger_str);
	ret_val = init_flanger_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_high_pass_filter(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_HIGH_PASS_FILTER;

	trans->compute_transformer    = calc_high_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_high_pass_filter_str *str = (m_eng_high_pass_filter_str*)malloc(sizeof(m_eng_high_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_high_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->cutoff_frequency, 1000.0, 1.0, 10000.0, 0.49995, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->cutoff_frequency)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_high_pass_filter_str);
	ret_val = init_high_pass_filter_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_low_end_compressor(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_LOW_END_COMPRESSOR;

	trans->compute_transformer    = calc_low_end_compressor;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 8);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_low_end_compressor_str *str = (m_eng_low_end_compressor_str*)malloc(sizeof(m_eng_low_end_compressor_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_low_end_compressor;
	trans->free_struct = NULL;

	init_parameter(&str->bass_comp.ratio, 2.0, 1.0, 10.0, 0.0045, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_comp.ratio)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->bass_comp.threshold, -12.0, 0.0, -30.0, 0.015, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_comp.threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->bass_comp.attack, 10.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_comp.attack)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->bass_comp.release, 200.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->bass_comp.release)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mids_comp.ratio, 2.0, 1.0, 10.0, 0.0045, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mids_comp.ratio)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mids_comp.threshold, -8.0, 0.0, -30.0, 0.015, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mids_comp.threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mids_comp.attack, 20.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mids_comp.attack)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->mids_comp.release, 200.0, 0.01, 250.0, 0.124995, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->mids_comp.release)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_low_end_compressor_str);
	ret_val = init_low_end_compressor_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_low_pass_filter(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_LOW_PASS_FILTER;

	trans->compute_transformer    = calc_low_pass_filter;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 1);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_low_pass_filter_str *str = (m_eng_low_pass_filter_str*)malloc(sizeof(m_eng_low_pass_filter_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_low_pass_filter;
	trans->free_struct = NULL;

	init_parameter(&str->cutoff_frequency, 100.0, 1.0, 10000.0, 0.49995, PARAMETER_SCALE_LOGARITHMIC);
	if ((ret_val = transformer_add_parameter(trans, &str->cutoff_frequency)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_low_pass_filter_str);
	ret_val = init_low_pass_filter_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_noise_suppressor(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_NOISE_SUPPRESSOR;

	trans->compute_transformer    = calc_noise_suppressor;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 3);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_noise_suppressor_str *str = (m_eng_noise_suppressor_str*)malloc(sizeof(m_eng_noise_suppressor_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = NULL;
	trans->free_struct = NULL;

	init_parameter(&str->threshold, -50, -100, -10, 0.045, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->max_reduction, -30, 0, -100, 0.05, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->max_reduction)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->ratio, 1.0, 0.0, 20.0, 0.01, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->ratio)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_noise_suppressor_str);
	ret_val = init_noise_suppressor_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_percussifier(m_transformer *trans)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	int ret_val = transformer_init_controls(trans);
	if (ret_val != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->type = TRANSFORMER_PERCUSSIFIER;

	trans->compute_transformer    = calc_percussifier;
	trans->compute_transformer_nl = NULL;
	trans->transition_policy = TRANSFORMER_TRANSITION_MONOBLOCK_LINEAR;

	ret_val = transformer_init_parameter_array(trans, 7);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	ret_val = transformer_init_setting_array(trans, 0);
	if (ret_val != NO_ERROR) { RETURN_ERR_CODE(ret_val); }
	m_eng_percussifier_str *str = (m_eng_percussifier_str*)malloc(sizeof(m_eng_percussifier_str));
	trans->data_struct = (void*)str;

	if (!str)
	{
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}

	trans->reconfigure = reconfigure_percussifier;
	trans->free_struct = NULL;

	init_parameter(&str->tempo, 120.0, 20, 300, 0.14, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->tempo)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->note, 16.0, 4.0, 32.0, 0.014, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->note)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->trigger_threshold, 3.0, 0.0, 4.0, 0.002, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->trigger_threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->arm_threshold, 1.5, 0.0, 2.0, 0.001, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->arm_threshold)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->fade_in, 2.9, 0.5, 10.0, 0.00475, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->fade_in)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->fade_out, 6, 0.5, 10.0, 0.00475, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->fade_out)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	init_parameter(&str->refractory_period, 100.0, 0.0, 700, 0.35, PARAMETER_SCALE_LINEAR);
	if ((ret_val = transformer_add_parameter(trans, &str->refractory_period)) != NO_ERROR)
	{
		RETURN_ERR_CODE(ret_val);
	}

	trans->clone_struct = NULL;
	trans->struct_size = sizeof(m_eng_percussifier_str);
	ret_val = init_percussifier_str(str);
	RETURN_ERR_CODE(ret_val);
}

int init_transformer(m_transformer *trans, uint16_t type)
{
	if (!trans)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}

	switch (type)
	{
		case TRANSFORMER_3_BAND_EQ:          return init_3_band_eq(trans);
		case TRANSFORMER_AMPLIFIER:          return init_amplifier(trans);
		case TRANSFORMER_BAND_PASS_FILTER:   return init_band_pass_filter(trans);
		case TRANSFORMER_COMPRESSOR:         return init_compressor(trans);
		case TRANSFORMER_DIRTY_OCTAVE:       return init_dirty_octave(trans);
		case TRANSFORMER_DISTORTION:         return init_distortion(trans);
		case TRANSFORMER_ENVELOPE:           return init_envelope(trans);
		case TRANSFORMER_FLANGER:            return init_flanger(trans);
		case TRANSFORMER_HIGH_PASS_FILTER:   return init_high_pass_filter(trans);
		case TRANSFORMER_LOW_END_COMPRESSOR: return init_low_end_compressor(trans);
		case TRANSFORMER_LOW_PASS_FILTER:    return init_low_pass_filter(trans);
		case TRANSFORMER_NOISE_SUPPRESSOR:   return init_noise_suppressor(trans);
		case TRANSFORMER_PERCUSSIFIER:       return init_percussifier(trans);
		default: RETURN_ERR_CODE(ERR_BAD_ARGS);
	}

	RETURN_ERR_CODE(NO_ERROR);
}
