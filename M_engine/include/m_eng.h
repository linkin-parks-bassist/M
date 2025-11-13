#ifndef M_MAIN_H_
#define M_MAIN_H_

#define AUDIO_BLOCK_SAMPLES  			128

#ifndef ARM_ASSEMBLY
#define AUDIO_SAMPLE_RATE_EXACT 		44100.0f

#define AUDIO_SAMPLE_RATE 				AUDIO_SAMPLE_RATE_EXACT
#define SAMPLE_FREQUENCY				0.0000226757369615

#define NUM_MASKS  						(((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

#ifndef M_ENGINE
#define M_ENGINE
#endif

//#define NO_CMSIS

#ifdef M_SIMULATED
#ifndef NO_CMSIS
#define NO_CMSIS
#endif
#endif

#define DC_BLOCKER_ALPHA 0.999

#ifndef M_SIMULATED
#include <arm_math.h>
#endif

#ifdef __cplusplus
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "utility/imxrt_hw.h"

extern "C" {
#else
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utility/imxrt_hw.h"
#endif

#ifdef M_SIMULATED

#define DMAMEM
#define FLASHMEM

#define __enable_irq()
#define __disable_irq()

#define PI   3.14159265
#endif

#define LN_2 0.69314718055994530942

#define MS_TO_SAMPLES(x) (((x) / 1000.0) * AUDIO_SAMPLE_RATE)
#define AUDIO_BLOCK_MS		(((float)AUDIO_BLOCK_SAMPLES * 1000.0) / (float)AUDIO_SAMPLE_RATE)

//#define ENABLE_LOGGING

#include "m_transformer_enum.h"
#include "m_error_codes.h"
#include "m_status.h"
#include "m_comms.h"

#include "m_alloc.h"

#define LL_MALLOC m_alloc
#define LL_FREE   m_free

#include "m_linked_list.h"

#include "m_parameter.h"
#include "m_transformer.h"
#include "m_pipeline.h"
#include "m_profile.h"

#include "m_eng_logging.h"

#include "m_eng_flops.h"
#include "m_eng_useful_functions.h"

#include "m_eng_audio_block.h"
#include "m_eng_mempool.h"

#include "m_eng_globals.h"

#include "m_eng_parameter.h"
#include "m_eng_transformer.h"
#include "m_eng_transformer_init.h"

#include "m_eng_buffer_mixer_amp.h"
#include "m_eng_linkowitz_riley.h"
#include "m_eng_equaliser.h"
#include "m_eng_pass_filter.h"
#include "m_eng_biquad.h"
#include "m_eng_compressor.h"
#include "m_eng_low_end_compressor.h"
#include "m_eng_waveshaper.h"
#include "m_eng_adaptive_waveshaper.h"
#include "m_eng_simple_distortion.h"
#include "m_eng_distortion.h"
#include "m_eng_dirty_octave.h"
#include "m_eng_noise_suppressor.h"
#include "m_eng_percussifier.h"
#include "m_eng_envelope.h"
#include "m_eng_flanger.h"
#include "m_eng_warbler.h"

#ifdef GRAPH_PIPELINE
#include "m_eng_graph.h"
#endif
#include "m_eng_pipeline.h"
#include "m_eng_pipeline_mod.h"
#include "m_eng_profile.h"
#include "m_eng_update.h"

#ifndef M_SIMULATED
#include "m_eng_i2s_dma.h"
#include "m_eng_sgtl5000.h"
#include "m_eng_memcpy_audio.h"
#endif

#include "m_eng_context.h"
#include "m_eng_comms.h"

#include "m_eng_transition.h"

#include "m_eng_debugging.h"

#ifndef M_SIMULATED
#include "m_eng_printf.h"
#else
#define m_printf printf
#include "M_teensy_simulator.h"
#endif

#define sqr(x) (x * x)

#define binary_max(x, y) ((x > y) ? x : y)
#define binary_min(x, y) ((x > y) ? y : x)

float trig_transition_function(float x);

#ifdef __cplusplus
}
#endif

#endif
#endif
