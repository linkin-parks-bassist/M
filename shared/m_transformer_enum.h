// Code generated from config/transformer/*.yaml by codegen.py
#ifndef M_TRANSFORMER_ENUM_H_
#define M_TRANSFORMER_ENUM_H_

#define TRANSFORMER_3_BAND_EQ          0
#define TRANSFORMER_AMPLIFIER          1
#define TRANSFORMER_BAND_PASS_FILTER   2
#define TRANSFORMER_COMPRESSOR         3
#define TRANSFORMER_DIRTY_OCTAVE       4
#define TRANSFORMER_DISTORTION         5
#define TRANSFORMER_ENVELOPE           6
#define TRANSFORMER_HIGH_PASS_FILTER   7
#define TRANSFORMER_LOW_END_COMPRESSOR 8
#define TRANSFORMER_LOW_PASS_FILTER    9
#define TRANSFORMER_NOISE_SUPPRESSOR   10
#define TRANSFORMER_PERCUSSIFIER       11

typedef enum
{
	low_pass		= 0,
	high_pass		= 1,
	band_pass 		= 2,
	notch 			= 3,
	peaking_band_eq = 4,
	low_shelf 		= 5,
	high_shelf 		= 6
} biquad_type;

#define DISTORTION_SOFT_FOLD 	0
#define DISTORTION_ARCTAN		1
#define DISTORTION_TANH			2
#define DISTORTION_CLIP			3

const char *transformer_type_to_string(uint16_t type);
int transformer_type_valid(uint16_t type);

#endif
