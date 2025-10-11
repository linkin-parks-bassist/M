#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "m_transformer_enum.h"

const char *transformer_type_to_string(uint16_t type)
{
	switch (type)
	{
		case TRANSFORMER_BUFFER:
			return "TRANSFORMER_BUFFER";
		case TRANSFORMER_AMPLIFIER:
			return "TRANSFORMER_AMPLIFIER";
		case TRANSFORMER_MIXER:
			return "TRANSFORMER_MIXER";
		case TRANSFORMER_BIQUAD:
			return "TRANSFORMER_BIQUAD";
		case TRANSFORMER_DISTORTION:
			return "TRANSFORMER_DISTORTION";
		case TRANSFORMER_COMPRESSOR:
			return "TRANSFORMER_COMPRESSOR";
		case TRANSFORMER_WAVESHAPER:
			return "TRANSFORMER_WAVESHAPER";
		case TRANSFORMER_LOW_PASS_FILTER:
			return "TRANSFORMER_LOW_PASS_FILTER";
		case TRANSFORMER_HIGH_PASS_FILTER:
			return "TRANSFORMER_HIGH_PASS_FILTER";
		case TRANSFORMER_BAND_PASS_FILTER:
			return "TRANSFORMER_BAND_PASS_FILTER";
		case TRANSFORMER_DIRTY_OCTAVE:
			return "TRANSFORMER_DIRTY_OCTAVE";
		default: return "UNKNOWN!";
	}
}
