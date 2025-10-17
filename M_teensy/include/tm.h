#ifndef M_MAIN_H_
#define M_MAIN_H_

#define AUDIO_BLOCK_SAMPLES  			128
#define AUDIO_SAMPLE_RATE_EXACT 		44100.0f

#define AUDIO_SAMPLE_RATE 				AUDIO_SAMPLE_RATE_EXACT
#define SAMPLE_FREQUENCY				0.0000226757369615

#ifndef TM_SIMULATED
#define tm_AudioNoInterrupts() 			(NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define tm_AudioInterrupts()   			(NVIC_ENABLE_IRQ(IRQ_SOFTWARE))
#else
#define tm_AudioNoInterrupts()
#define tm_AudioInterrupts()
#endif

#define NUM_MASKS  						(((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

#define M_TEENSY

#define NO_CMSIS

#ifdef TM_SIMULATED
#ifndef NO_CMSIS
#define NO_CMSIS
#endif
#endif

#define DC_BLOCKER_ALPHA 0.999

#ifndef TM_SIMULATED
#include <arm_math.h>

#include <DMAChannel.h>
#include <TeensyThreads.h>

#include <Wire.h>

#include "utility/imxrt_hw.h"
#endif

#ifdef __cplusplus
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#else
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#endif

#ifdef TM_SIMULATED

#define DMAMEM
#define FLASHMEM

#define __enable_irq()
#define __disable_irq()

#define PI   3.14159265
#endif

#define LN_2 0.69314718055994530942

#include "m_transformer_enum.h"
#include "m_error_codes.h"
#include "m_status.h"
#include "m_comms.h"
#include "m_linked_list.h"

#include "tm_audio_block.h"
#include "tm_mempool.h"

#include "tm_globals.h"

#include "tm_parameter.h"
#include "tm_transformer.h"
#include "tm_transformer_init.h"

#include "tm_buffer_mixer_amp.h"
#include "tm_linkowitz_riley.h"
#include "tm_equaliser.h"
#include "tm_pass_filter.h"
#include "tm_biquad.h"
#include "tm_compressor.h"
#include "tm_waveshaper.h"
#include "tm_distortion.h"
#include "tm_dirty_octave.h"
#include "tm_noise_suppressor.h"
#include "tm_percussifier.h"

#include "tm_pipeline.h"
#include "tm_pipe_line.h"
#include "tm_pipeline_mod.h"
#include "tm_profile.h"
#include "tm_update.h"

#ifndef TM_SIMULATED
#include "tm_i2s_dma.h"
#include "tm_sgtl5000.h"
#include "tm_memcpy_audio.h"
#endif

#include "tm_context.h"
#include "tm_comms.h"

#include "tm_transition.h"

#include "tm_debugging.h"

#ifndef TM_SIMULATED
#include "tm_printf.h"
#else
#define tm_printf printf
#include "M_teensy_simulator.h"
#endif

#define sqr(x) (x * x)

#define binary_max(x, y) ((x > y) ? x : y)
#define binary_min(x, y) ((x > y) ? y : x)

float trig_transition_function(float x);

#endif
