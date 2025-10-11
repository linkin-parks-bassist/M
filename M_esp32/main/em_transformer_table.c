// Code generated from transformer_config.yaml by codegen_esp32.py
#include "em.h"

const int N_TRANSFORMER_TYPES = 9;

em_trans_desc transformer_table[] = {
	(em_trans_desc){"Buffer",           TRANSFORMER_BUFFER},
	(em_trans_desc){"Amplifier",        TRANSFORMER_AMPLIFIER},
	(em_trans_desc){"Biquad",           TRANSFORMER_BIQUAD},
	(em_trans_desc){"Distortion",       TRANSFORMER_DISTORTION},
	(em_trans_desc){"Compressor",       TRANSFORMER_COMPRESSOR},
	(em_trans_desc){"Low Pass Filter",  TRANSFORMER_LOW_PASS_FILTER},
	(em_trans_desc){"High Pass Filter", TRANSFORMER_HIGH_PASS_FILTER},
	(em_trans_desc){"Band Pass Filter", TRANSFORMER_BAND_PASS_FILTER},
	(em_trans_desc){"Dirty Octave",     TRANSFORMER_DIRTY_OCTAVE},
};
