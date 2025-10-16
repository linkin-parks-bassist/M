#include "em.h"

const int N_TRANSFORMER_TYPES = 9;

em_trans_desc transformer_table[] = {
	(em_trans_desc){"Amplifier",        TRANSFORMER_AMPLIFIER},
	(em_trans_desc){"Compressor",       TRANSFORMER_COMPRESSOR},
	(em_trans_desc){"Low Pass Filter",  TRANSFORMER_LOW_PASS_FILTER},
	(em_trans_desc){"High Pass Filter", TRANSFORMER_HIGH_PASS_FILTER},
	(em_trans_desc){"Band Pass Filter", TRANSFORMER_BAND_PASS_FILTER},
	(em_trans_desc){"Dirty Octave",     TRANSFORMER_DIRTY_OCTAVE},
	(em_trans_desc){"Noise Suppressor", TRANSFORMER_NOISE_SUPPRESSOR},
	(em_trans_desc){"Percussifier",     TRANSFORMER_PERCUSSIFIER},
	(em_trans_desc){"Distortion",       TRANSFORMER_DISTORTION}
};
