// Code generated from config/transformer/*.yaml by codegen.py
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "m_transformer_enum.h"

static const char *FNAME = "m_transformer_enum.c";

const char *transformer_type_to_string(uint16_t type)
{
	 switch(type)
	{
		case TRANSFORMER_3_BAND_EQ:          return "TRANSFORMER_3_BAND_EQ";
		case TRANSFORMER_AMPLIFIER:          return "TRANSFORMER_AMPLIFIER";
		case TRANSFORMER_BAND_PASS_FILTER:   return "TRANSFORMER_BAND_PASS_FILTER";
		case TRANSFORMER_COMPRESSOR:         return "TRANSFORMER_COMPRESSOR";
		case TRANSFORMER_DIRTY_OCTAVE:       return "TRANSFORMER_DIRTY_OCTAVE";
		case TRANSFORMER_DISTORTION:         return "TRANSFORMER_DISTORTION";
		case TRANSFORMER_ENVELOPE:           return "TRANSFORMER_ENVELOPE";
		case TRANSFORMER_FLANGER:            return "TRANSFORMER_FLANGER";
		case TRANSFORMER_HIGH_PASS_FILTER:   return "TRANSFORMER_HIGH_PASS_FILTER";
		case TRANSFORMER_LOW_END_COMPRESSOR: return "TRANSFORMER_LOW_END_COMPRESSOR";
		case TRANSFORMER_LOW_PASS_FILTER:    return "TRANSFORMER_LOW_PASS_FILTER";
		case TRANSFORMER_NOISE_SUPPRESSOR:   return "TRANSFORMER_NOISE_SUPPRESSOR";
		case TRANSFORMER_PERCUSSIFIER:       return "TRANSFORMER_PERCUSSIFIER";
		case TRANSFORMER_WARBLER:            return "TRANSFORMER_WARBLER";
		default: return "UNKNOWN";
	}
}

int transformer_type_valid(uint16_t type)
{
	 switch(type)
	{
		case TRANSFORMER_3_BAND_EQ: 
		case TRANSFORMER_AMPLIFIER: 
		case TRANSFORMER_BAND_PASS_FILTER: 
		case TRANSFORMER_COMPRESSOR: 
		case TRANSFORMER_DIRTY_OCTAVE: 
		case TRANSFORMER_DISTORTION: 
		case TRANSFORMER_ENVELOPE: 
		case TRANSFORMER_FLANGER: 
		case TRANSFORMER_HIGH_PASS_FILTER: 
		case TRANSFORMER_LOW_END_COMPRESSOR: 
		case TRANSFORMER_LOW_PASS_FILTER: 
		case TRANSFORMER_NOISE_SUPPRESSOR: 
		case TRANSFORMER_PERCUSSIFIER: 
		case TRANSFORMER_WARBLER: 
			return 1;
		default:
			return 0;
	}
}
