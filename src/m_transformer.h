#ifndef M_TRANSFORMER_H_
#define M_TRANSFORMER_H_

typedef struct
{
	int x, y;
} vec2i;

#define MAX_TRANSFER_INPUTS		4
#define MAX_TRANSFER_OUTPUTS	4

#define TRANSFORMER_BUFFER			0
#define TRANSFORMER_SUB_PIPELINE 	1
#define TRANSFORMER_MIXER			2
#define TRANSFORMER_AMPLIFIER		3
#define TRANSFORMER_FADER			4

#define FADER_FADE_IN  0
#define FADER_FADE_OUT 1


typedef struct
{
	float gain;
} m_trans_amp_data;

typedef struct
{
	float gains[2];
} m_trans_mixer_data;

typedef struct
{
	int fade_type;
	
	uint32_t sample_progress;
	uint32_t duration_samples;
} m_trans_fader_data;

typedef struct
{
	int type;
	
	unsigned int n_inputs, n_outputs;
	
	vec2i inputs [MAX_TRANSFER_INPUTS ];
	vec2i outputs[MAX_TRANSFER_OUTPUTS];

	void *data;
} m_audio_transformer;

int init_buffer_transformer(m_audio_transformer *trans, vec2i input, vec2i output);
int init_amp_transformer(m_audio_transformer *trans, float gain, vec2i input, vec2i output);

#endif
