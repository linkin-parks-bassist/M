#ifndef ESP32_CONTEXT_H_
#define ESP32_CONTEXT_H_

#define MAX_N_PROFILES 256

typedef struct
{
	int x;
	int y;
} vec2i;

/* Stripped-down structs to keep track of what is going on in Teensyland */
typedef struct
{
	int type;
	int n_inputs;
	int n_outputs;
	
	int n_parameters;
	m_parameter *params;
} teensy_transformer;

typedef struct
{
	int width, height;
	
	int n_transformers;
	
} teensy_pipeline;

typedef struct
{
	teensy_pipeline pipeline;
} teensy_profile;

typedef struct
{
	int n_profiles;
	int active_profile;
	
	teensy_profile profiles[MAX_N_PROFILES];
} teensy_context;

#endif
