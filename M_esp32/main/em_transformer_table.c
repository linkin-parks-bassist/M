// Code generated from transformer_config.yaml by codegen_esp32.py
#include "em.h"

const int N_TRANSFORMER_TYPES = 4;

em_trans_desc transformer_table[] = {
	(em_trans_desc){"Buffer",     TRANSFORMER_BUFFER},
	(em_trans_desc){"Amplifier",  TRANSFORMER_AMPLIFIER},
	(em_trans_desc){"Distortion", TRANSFORMER_DISTORTION},
	(em_trans_desc){"Compressor", TRANSFORMER_COMPRESSOR},
};
