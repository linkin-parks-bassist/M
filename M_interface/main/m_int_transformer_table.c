#include "m_int.h"

static const char *FNAME = "m_int_transformer_table.c";

const int N_TRANSFORMER_TYPES = 12;

m_int_trans_desc transformer_table[] = {
	(m_int_trans_desc){"3 Band Eq",          TRANSFORMER_3_BAND_EQ},
	(m_int_trans_desc){"Amplifier",          TRANSFORMER_AMPLIFIER},
	(m_int_trans_desc){"Band Pass Filter",   TRANSFORMER_BAND_PASS_FILTER},
	(m_int_trans_desc){"Compressor",         TRANSFORMER_COMPRESSOR},
	(m_int_trans_desc){"Dirty Octave",       TRANSFORMER_DIRTY_OCTAVE},
	(m_int_trans_desc){"Distortion",         TRANSFORMER_DISTORTION},
	(m_int_trans_desc){"Envelope",           TRANSFORMER_ENVELOPE},
	(m_int_trans_desc){"High Pass Filter",   TRANSFORMER_HIGH_PASS_FILTER},
	(m_int_trans_desc){"Low End Compressor", TRANSFORMER_LOW_END_COMPRESSOR},
	(m_int_trans_desc){"Low Pass Filter",    TRANSFORMER_LOW_PASS_FILTER},
	(m_int_trans_desc){"Noise Suppressor",   TRANSFORMER_NOISE_SUPPRESSOR},
	(m_int_trans_desc){"Percussifier",       TRANSFORMER_PERCUSSIFIER}
};
