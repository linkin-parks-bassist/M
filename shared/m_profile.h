#ifndef M_PROFILE_H_
#define M_PROFILE_H_

#ifdef M_INTERFACE
	struct m_int_glide_button_pll;
	struct m_int_menu_item_pll;
#endif

#ifdef M_ENGINE
	struct m_pipeline_mod_ll;
#endif

typedef struct m_profile
{
	int active;
	
	#if defined(M_ENGINE)
	m_pipeline *front_pipeline;
	m_pipeline *back_pipeline;
	
	int pipelines_swapping;
	int pipeline_swap_progress;
	int pipeline_swap_samples;
	int pipeline_swap_type;
	int back_pipeline_warmed_up;
	
	struct m_pipeline_mod_ll *jobs;
	struct m_pipeline_mod_ll *ujobs;
	
	int transition_policy;
	
	float *prev_block;
	
	m_transformer output_amp;
	
	#elif defined(M_INTERFACE)
	
	char *name;
	uint16_t id;
	m_pipeline pipeline;
	
	struct m_ui_page *view_page;
	
	struct m_int_menu_item_pll *listings;
	struct m_int_glide_button_pll *gbs;
	
	m_parameter volume;
	
	char *fname;
	
	int default_profile;
	int unsaved_changes;
	
	#endif
} m_profile;

#endif
