#include <Wire.h>

#include "src/M.h"

m_pipeline pipeline;

#define BYPASS
//#define DISTORTION
//#define COMPRESSION

void setup()
{
	delay(1000);
	Serial.end();
	
	m_printf("Initialising i2s...\n");
	init_i2s();
	
	init_mem_pools();
	
	m_printf("Initialising sgtl5000...\n");
	sgtl5000_enable();
	sgtl5000_line_in_level(4);
	sgtl5000_volume(0.75); 
	//sgtl5000_adc_high_pass_filter_disable();
	
	int ret_val;
	
	#ifdef BYPASS
	init_bypass_pipeline(&pipeline);
	#else
	#ifdef DISTORTION
	float f_1 = 100.0;
	float f_2 = 1000.0;
	
	float gains[4] = {0.6, 0.2, 0.2, 0.4};
	vec2i mixer_inputs[4] = {(vec2i){2, 0}, (vec2i){2, 1}, (vec2i){2, 2}, INPUT_NODE_COORD};
	
	init_pipeline(&pipeline, 4, 3);
	
	pipeline_activate_node(&pipeline, 0, 0);
	pipeline_activate_node(&pipeline, 0, 1);
	pipeline_activate_node(&pipeline, 0, 2);
	pipeline_activate_node(&pipeline, 1, 0);
	pipeline_activate_node(&pipeline, 1, 1);
	pipeline_activate_node(&pipeline, 1, 2);
	pipeline_activate_node(&pipeline, 2, 0);
	pipeline_activate_node(&pipeline, 2, 1);
	pipeline_activate_node(&pipeline, 2, 2);
	pipeline_activate_node(&pipeline, 3, 0);
	
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
	pipeline_add_transformer(&pipeline, alloc_tanh_distortion((vec2i){1, 1},  (vec2i){2, 1}, 12.0));
	
	/* Distort highs */
	pipeline_add_transformer(&pipeline, alloc_tanh_distortion((vec2i){1, 2},  (vec2i){2, 2}, 14.0));
	
	pipeline_add_transformer(&pipeline, alloc_mixer_transformer(mixer_inputs, 4, (vec2i){3, 0}, gains));
	pipeline_add_transformer(&pipeline, alloc_compressor1((vec2i){3, 0}, OUTPUT_NODE_COORD, 6.0, -18, 0.01, 0.03));
	
	#else
	#ifdef COMPRESSION
	init_pipeline(&pipeline, 0, 0);
	
	if ((ret_val = pipeline_add_transformer(&pipeline, alloc_compressor1(INPUT_NODE_COORD, OUTPUT_NODE_COORD, 20.0, -30.0, 0.0001, 0.005))) != NO_ERROR)
	{
		m_printf("Error adding compressor: %d\n", ret_val);
	}
	else
	{
		m_printf("Sucessfully added compressor\n");
	}
	#endif
	#endif
	#endif
	
	set_active_pipeline(&pipeline);
	
	m_printf("Initialisation complete.\n");
}

void loop()
{
	
}
