#include <Wire.h>

#include "src/M.h"

m_pipeline pipeline;

//#define BYPASS

void setup()
{
	delay(1000);
	
	m_printf("Initialising i2s...\n");
	init_i2s();
	
	init_mem_pools();
	
	m_printf("Initialising sgtl5000...\n");
	sgtl5000_enable();
	sgtl5000_line_in_level(4);
	sgtl5000_volume(0.75); 
	
	#ifdef BYPASS
	init_bypass_pipeline(&pipeline);
	#else
	float f_1 = 100.0;
	float f_2 = 1000.0;
	
	float gains[4] = {0.2, 0.2, 0.2, 0.2};
	vec2i mixer_inputs[4] = {(vec2i){2, 0}, (vec2i){2, 1}, (vec2i){2, 2}, INPUT_NODE_COORD};
	
	
	init_pipeline(&pipeline, 3, 9);
	
	pipeline_activate_node(&pipeline, 0, 0);
	pipeline_activate_node(&pipeline, 0, 1);
	pipeline_activate_node(&pipeline, 0, 2);
	pipeline_activate_node(&pipeline, 1, 0);
	pipeline_activate_node(&pipeline, 1, 1);
	pipeline_activate_node(&pipeline, 1, 2);
	pipeline_activate_node(&pipeline, 2, 0);
	pipeline_activate_node(&pipeline, 2, 1);
	pipeline_activate_node(&pipeline, 2, 2);
	
	/* Split out bass */
	pipeline_add_transformer(&pipeline, alloc_low_pass_transformer(INPUT_NODE_COORD,  (vec2i){0, 0}, f_1));
	pipeline_add_transformer(&pipeline, alloc_low_pass_transformer((vec2i){0, 0}, 	  (vec2i){2, 0}, f_1));
	
	/* Split out mids */
	pipeline_add_transformer(&pipeline, alloc_band_pass_transformer(INPUT_NODE_COORD, (vec2i){0, 1}, sqrt(f_1 * f_2), log2f(f_2 / f_1)));
	pipeline_add_transformer(&pipeline, alloc_band_pass_transformer((vec2i){0, 1}, 	  (vec2i){1, 1}, sqrt(f_1 * f_2), log2f(f_2 / f_1)));
	
	/* Split out highs */
	pipeline_add_transformer(&pipeline, alloc_high_pass_transformer(INPUT_NODE_COORD, (vec2i){0, 2}, f_2));
	pipeline_add_transformer(&pipeline, alloc_high_pass_transformer((vec2i){0, 2}, 	  (vec2i){1, 2}, f_2));
	
	/* Distort mids */
	pipeline_add_transformer(&pipeline, alloc_arctan_dist_transformer((vec2i){1, 1},  (vec2i){2, 1}, 9.0));
	
	/* Distort highs */
	pipeline_add_transformer(&pipeline, alloc_arctan_dist_transformer((vec2i){1, 2},  (vec2i){2, 2}, 6.0));
	
	pipeline_add_transformer(&pipeline, alloc_mixer_transformer(mixer_inputs, 4, OUTPUT_NODE_COORD, gains));
	
	#endif
	
	set_active_pipeline(&pipeline);
	
	m_printf("Initialisation complete.\n");
}

void loop()
{
	
}
