// Code generated from config/transformer/*.yaml by codegen.py
#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "m_transformer_enum.h"

const char *transformer_type_to_string(uint16_t type)
{
	 switch(type)
	{
		case TRANSFORMER_AMPLIFIER:        return "TRANSFORMER_AMPLIFIER";
		case TRANSFORMER_COMPRESSOR:       return "TRANSFORMER_COMPRESSOR";
		case TRANSFORMER_LOW_PASS_FILTER:  return "TRANSFORMER_LOW_PASS_FILTER";
		case TRANSFORMER_HIGH_PASS_FILTER: return "TRANSFORMER_HIGH_PASS_FILTER";
		case TRANSFORMER_BAND_PASS_FILTER: return "TRANSFORMER_BAND_PASS_FILTER";
		case TRANSFORMER_DIRTY_OCTAVE:     return "TRANSFORMER_DIRTY_OCTAVE";
		case TRANSFORMER_NOISE_SUPPRESSOR: return "TRANSFORMER_NOISE_SUPPRESSOR";
		case TRANSFORMER_PERCUSSIFIER:     return "TRANSFORMER_PERCUSSIFIER";
		case TRANSFORMER_DISTORTION:       return "TRANSFORMER_DISTORTION";
		default: return "UNKNOWN";
	}
}

int transformer_type_valid(uint16_t type)
{
	 switch(type)
	{
		case TRANSFORMER_AMPLIFIER: 
		case TRANSFORMER_COMPRESSOR: 
		case TRANSFORMER_LOW_PASS_FILTER: 
		case TRANSFORMER_HIGH_PASS_FILTER: 
		case TRANSFORMER_BAND_PASS_FILTER: 
		case TRANSFORMER_DIRTY_OCTAVE: 
		case TRANSFORMER_NOISE_SUPPRESSOR: 
		case TRANSFORMER_PERCUSSIFIER: 
		case TRANSFORMER_DISTORTION: 
			return 1;
		default:
			return 0;
	}
}
