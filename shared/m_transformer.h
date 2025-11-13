#ifndef M_TRANSFORMER_H_
#define M_TRANSFORMER_H_

#ifdef M_INTERFACE
	struct m_ui_page;
#endif

#ifdef M_ENGINE
	#include "m_eng_linkowitz_riley.h"
#endif

typedef struct m_transformer
{
	uint16_t type;
	uint16_t id;
	
	m_parameter wet_mix;
	
	m_setting band_mode;
	m_parameter band_lp_cutoff;
	m_parameter band_hp_cutoff;
	m_parameter band_center;
	m_parameter band_width;
	
	#if defined(M_ENGINE)
	
	int n_settings;
	int setting_array_size;
	
	m_setting **settings;
	
	int n_parameters;
	int parameter_array_size;
	m_parameter **parameters;
	
	struct m_lr_low_pass_filter_str  input_lpf;
	struct m_lr_high_pass_filter_str input_hpf;
	
	void *data_struct;
	int (*compute_transformer)(void *data_struct, float *dest, float *src, int n_samples);
	int (*compute_transformer_nl)(void *data_struct, float **dest, float **src, int n_samples);
	
	int (*reconfigure)(void *data_struct);
	int (*clone_struct)(void *dest, void *src);
	int (*free_struct)(void *data_struct);
	
	size_t struct_size;
	int transition_policy;
	
	#elif defined(M_INTERFACE)
	
	int position;
	
	m_parameter_pll *parameters;
	m_setting_pll *settings;
	
	struct m_profile *profile;
	struct m_ui_page *view_page;
	
	#endif
} m_transformer;

DECLARE_LINKED_PTR_LIST(m_transformer);

#endif
