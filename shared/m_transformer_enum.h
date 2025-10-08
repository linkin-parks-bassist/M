// Code generated from transformer_config.yaml by codegen_enum.py
#ifndef M_TRANSFORMER_ENUM_H_
#define M_TRANSFORMER_ENUM_H_

#define TRANSFORMER_BUFFER     0
#define TRANSFORMER_AMPLIFIER  1
#define TRANSFORMER_MIXER      2
#define TRANSFORMER_BIQUAD     3
#define TRANSFORMER_DISTORTION 4
#define TRANSFORMER_COMPRESSOR 5
#define TRANSFORMER_WAVESHAPER 6

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

#endif
