#ifndef M_BMA_H_
#define M_BMA_H_

typedef struct
{
	tm_parameter gain;
} tm_amplifier_str;

typedef struct
{
	tm_parameter ratio;
} tm_mixer_str;

int init_buffer(tm_transformer *trans, vec2i input, vec2i output);
tm_transformer *alloc_buffer_transformer(vec2i input, vec2i output);

int init_amplifier_struct_default(tm_amplifier_str *str);
int init_amplifier(tm_transformer *trans, vec2i input, vec2i output, float gain);
tm_transformer *alloc_amplifier_transformer(vec2i input, vec2i output, float gain);

int init_mixer_struct_default(tm_mixer_str *str);
int init_mixer(tm_transformer *trans, vec2i *inputs, vec2i output, float gain_1);
tm_transformer *alloc_mixer_transformer(vec2i *inputs, vec2i output, float gain_2);

int init_buffer_default	(tm_transformer *trans);
int init_amplifier_default	(tm_transformer *trans);
int init_mixer_default	(tm_transformer *trans);

int calc_mixer(void *data_struct, float **dest, float **src, int n_samples);
int calc_buffer(void *data_struct, float **dest, float **src, int n_samples);
int calc_amplifier(void *data_struct, float **dest, float **src, int n_samples);

#endif
