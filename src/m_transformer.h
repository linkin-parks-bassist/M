#ifndef M_TRANSFORMER_H_
#define M_TRANSFORMER_H_

typedef struct
{
	int x, y;
} vec2i;

#define MAX_TRANSFORMER_INPUTS		4
#define MAX_TRANSFORMER_OUTPUTS		4

#define TRANSFORMER_BUFFER			0
#define TRANSFORMER_SUB_PIPELINE 	1
#define TRANSFORMER_MIXER			2
#define TRANSFORMER_AMPLIFIER		3
#define TRANSFORMER_FADER			4
#define TRANSFORMER_BIQUAD			5
#define TRANSFORMER_WAVESHAPER		6
#define TRANSFORMER_DISTORTION		7
#define TRANSFORMER_COMPRESSOR		8

#define FADER_FADE_IN  0
#define FADER_FADE_OUT 1

#define LN_2 0.69314718055994530942

//#define PRINT_TRANSFORMER_INFO

#define TRANSFORMER_SWITCH_ACTION_BYPASS 0

typedef struct
{
	int type;
	
	unsigned int n_inputs, n_outputs;
	
	int bypass;
	
	vec2i inputs [MAX_TRANSFORMER_INPUTS ];
	vec2i outputs[MAX_TRANSFORMER_OUTPUTS];

	int n_parameters;
	m_parameter **parameters;
	
	void *transformer_data;
	int (*compute_transformer)(float **dest, float **src, void *transformer_data);
} m_audio_transformer;

int init_transformer(m_audio_transformer *trans, int type,
					 unsigned int n_inputs,  unsigned int n_outputs,
					 vec2i 		   *inputs,  vec2i 		  *outputs,
					 int n_parameters,
					 void *transformer_data,
					 int (*compute_transformer)(float **dest, float **src, void *transformer_data));

int transformer_add_parameter(m_audio_transformer *trans, m_parameter *param);

#endif
