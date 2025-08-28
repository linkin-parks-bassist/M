/* m_Audio Library for Teensy 3.X
 *Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 *Development of this audio library was funded by PJRC.COM, LLC by sales of
 *Teensy and m_Audio Adaptor boards.  Please support PJRC's efforts to develop
 *open source software by purchasing Teensy or other PJRC products.
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice, development funding notice, and this permission
 *notice shall be included in all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 */

#ifndef m_Audio_h_
#define m_Audio_h_

#if TEENSYDUINO < 120
#error "Teensyduino version 1.20 or later is required to compile the m_Audio library."
#endif
#ifdef __AVR__
#error "The m_Audio Library only works with 32 bit Teensy models.  Teensy 2.0 is unsupported."
#endif

#include <DMAChannel.h>  // github.com/PaulStoffregen/cores/blob/master/teensy4/DMAChannel.h
#if !defined(DMACHANNEL_HAS_BEGIN) || !defined(DMACHANNEL_HAS_BOOLEAN_CTOR)
#error "You need to update DMAChannel.h & DMAChannel.cpp"
#error "https://github.com/PaulStoffregen/cores/blob/master/teensy3/DMAChannel.h"
#error "https://github.com/PaulStoffregen/cores/blob/master/teensy3/DMAChannel.cpp"
#endif

// When changing multiple audio object settings that must update at
// the same time, these functions allow the audio library interrupt
// to be disabled.  For example, you may wish to begin playing a note
// in response to reading an analog sensor.  If you have "velocity"
// information, you might start the sample playing and also adjust
// the gain of a mixer channel.  Use m_AudioNoInterrupts() first, then
// make both changes to the 2 separate objects.  Then allow the audio
// library to update with m_AudioInterrupts().  Both changes will happen
// at the same time, because m_AudioNoInterrupts() prevents any updates
// while you make changes.
//
#define m_AudioNoInterrupts() (NVIC_DISABLE_IRQ(IRQ_SOFTWARE))
#define m_AudioInterrupts()   (NVIC_ENABLE_IRQ(IRQ_SOFTWARE))

#define MAX_AUDIO_MEMORY 229376

#define NUM_MASKS  (((MAX_AUDIO_MEMORY / AUDIO_BLOCK_SAMPLES / 2) + 31) / 32)

// include all the library headers, so a sketch can use a single
// #include "m_m_Audio.h" to get the whole library
//
#include <DMAChannel.h>
#include "m_audiostream.h"
#include "m_audiocontrol.h"
#include "m_i2s_dma.h"
#include "m_control_sgtl5000.h"
#include "m_memcpy_audio.h"

#endif
