#ifndef M_MAIN_H_
#define M_MAIN_H_

#define AUDIO_BLOCK_SAMPLES  			128
#define AUDIO_SAMPLE_RATE_EXACT 		44100.0f

#define AUDIO_SAMPLE_RATE 				AUDIO_SAMPLE_RATE_EXACT


#define m_AudioNoInterrupts() 			(NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define m_AudioInterrupts()   			(NVIC_ENABLE_IRQ(IRQ_SOFTWARE))

#define NUM_MASKS  						(((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

#include <DMAChannel.h>

#include "m_printf.h"
#include "m_error_codes.h"

#include "utility/imxrt_hw.h"
#include "m_audio_block.h"
#include "m_mempool.h"

#include "m_globals.h"

#include "m_transformer.h"
#include "m_pipeline.h"
#include "m_update.h"

#include "m_i2s_dma.h"
#include "m_sgtl5000.h"
#include "m_memcpy_audio.h"

#endif
