#ifndef M_MAIN_H_
#define M_MAIN_H_

#define AUDIO_BLOCK_SAMPLES  			128
#define AUDIO_SAMPLE_RATE_EXACT 		44100.0f

#define AUDIO_SAMPLE_RATE 				AUDIO_SAMPLE_RATE_EXACT


#define tm_AudioNoInterrupts() 			(NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define tm_AudioInterrupts()   			(NVIC_ENABLE_IRQ(IRQ_SOFTWARE))

#define NUM_MASKS  						(((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

#define M_TEENSY

#define NO_CMSIS

#define DC_BLOCKER_ALPHA 0.999

#include <arm_math.h>

#include <DMAChannel.h>
#include <TeensyThreads.h>

#include "utility/imxrt_hw.h"

#include "m_transformer_enum.h"
#include "m_error_codes.h"
#include "m_status.h"
#include "m_comms.h"
#include "m_linked_list.h"

#include "tm_printf.h"

#include "tm_audio_block.h"
#include "tm_mempool.h"

#include "tm_globals.h"

#include "tm_parameter.h"
#include "tm_transformer.h"
#include "tm_transformer_init.h"

#include "tm_buffer_mixer_amp.h"
#include "tm_biquad.h"
#include "tm_normalised_biquad.h"
#include "tm_compressor.h"
#include "tm_waveshaper.h"
#include "tm_distortion.h"
#include "tm_pass_filter.h"
#include "tm_dirty_octave.h"

#include "tm_pipeline.h"
#include "tm_pipeline_mod.h"
#include "tm_profile.h"
#include "tm_update.h"

#include "tm_i2s_dma.h"
#include "tm_sgtl5000.h"
#include "tm_memcpy_audio.h"

#include "tm_context.h"
#include "tm_comms.h"

#include "tm_transition.h"

#include "tm_debugging.h"

#define sqr(x) (x * x)

#define binary_max(x, y) ((x > y) ? x : y)
#define binary_min(x, y) ((x > y) ? y : x)

float trig_transition_function(float x);

#endif
