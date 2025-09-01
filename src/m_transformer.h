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
#define TRANSFORMER_ARCTAN_DIST		6

#define FADER_FADE_IN  0
#define FADER_FADE_OUT 1

#define LN_2 0.69314718055994530942

#define PRINT_TRANSFORMER_INFO

typedef struct
{
	float gain;
} m_trans_amp_data;

typedef struct
{
	int n_inputs;
	float *gains;
} m_trans_mixer_data;

typedef struct
{
	int fade_type;
	
	uint32_t sample_progress;
	uint32_t duration_samples;
} m_trans_fader_data;

enum biquad_type
{
    low_pass,
    high_pass,
    band_pass,
    notch,
    peaking_band_eq,
    low_shelf,
    high_shelf
};

typedef struct
{
	int type;
	
	float a0, a1, a2, a3, a4;
    float x1, x2, y1, y2;
} m_trans_biquad_data;

typedef struct
{
	float coef;
	
	float running_amp;
	float prev_block[AUDIO_BLOCK_SAMPLES];
} m_trans_arctan_dist_data;

typedef struct
{
	int type;
	
	unsigned int n_inputs, n_outputs;
	
	vec2i inputs [MAX_TRANSFORMER_INPUTS ];
	vec2i outputs[MAX_TRANSFORMER_OUTPUTS];

	void *transformer_data;
	
	int (*compute_transformer)(float **dest, float **src, void *transformer_data);
} m_audio_transformer;

int init_buffer_transformer(m_audio_transformer *trans, vec2i input, vec2i output);
m_audio_transformer *alloc_buffer_transformer(vec2i input, vec2i output);

int init_amp_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float gain);
m_audio_transformer *alloc_amp_transformer(vec2i input, vec2i output, float gain);

int init_mixer_transformer(m_audio_transformer *trans, vec2i *inputs, int n_inputs, vec2i output, float *gains);
m_audio_transformer *alloc_mixer_transformer(vec2i *inputs, int n_inputs, vec2i output, float *gains);

int init_fader_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int fade_type, uint32_t duration_samples);
m_audio_transformer *alloc_fader_transformer(vec2i input, vec2i output, int fade_type, uint32_t duration_samples);

int init_biquad_transformer(m_audio_transformer *trans, vec2i input, vec2i output, int type, float cutoff, float bandwidth, float db_gain);
m_audio_transformer *alloc_biquad_transformer(vec2i input, vec2i output, int fade_type, uint32_t duration_samples);

int init_low_pass_transformer (m_audio_transformer *trans, vec2i input, vec2i output, float cutoff);
int init_high_pass_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float cutoff);
int init_band_pass_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float center, float bandwidth);
m_audio_transformer *alloc_low_pass_transformer (vec2i input, vec2i output, float cutoff);
m_audio_transformer *alloc_high_pass_transformer(vec2i input, vec2i output, float cutoff);
m_audio_transformer *alloc_band_pass_transformer(vec2i input, vec2i output, float center, float bandwidth);

int init_arctan_dist_transformer(m_audio_transformer *trans, vec2i input, vec2i output, float coef);
m_audio_transformer *alloc_arctan_dist_transformer(vec2i input, vec2i output, float coef);

#endif
