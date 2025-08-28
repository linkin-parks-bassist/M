/* Teensyduino Core Library
 *http://www.pjrc.com/teensy/
 *Copyright (c) 2017 PJRC.COM, LLC.
 *
 *Permission is hereby granted, free of charge, to any person obtaining
 *a copy of this software and associated documentation files (the
 *"Software"), to deal in the Software without restriction, including
 *without limitation the rights to use, copy, modify, merge, publish,
 *distribute, sublicense, and/or sell copies of the Software, and to
 *permit persons to whom the Software is furnished to do so, subject to
 *the following conditions:
 *
 *1. The above copyright notice and this permission notice shall be
 *included in all copies or substantial portions of the Software.
 *
 *2. If the Software is incorporated into a build system that allows
 *selection among a list of target devices, then similar target
 *devices manufactured by PJRC.COM must be included in the list of
 *target devices and selectable in the same manner.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 *BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 *ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 */

#ifndef m_audio_stream_h
#define m_audio_stream_h

#ifndef __ASSEMBLER__
#include <stdio.h>  // for NULL
#include <string.h> // for memcpy

#endif

// AUDIO_BLOCK_SAMPLES determines how many samples the audio library processes
// per update.  It may be reduced to achieve lower latency response to events,
// at the expense of higher interrupt and DMA setup overhead.
//
// Less than 32 may not work with some input & output objects.  Multiples of 16
// should be used, since some synthesis objects generate 16 samples per loop.
//
// Some parts of the audio library may have hard-coded dependency on 128 samples.
// Please report these on the forum with reproducible test cases.  The following
// audio classes are known to have problems with smaller block sizes:
//   m_AudioInputUSB, m_AudioOutputUSB, m_AudioPlaySdWav, m_AudioAnalyzeFFT256,
//   m_AudioAnalyzeFFT1024

#ifndef AUDIO_BLOCK_SAMPLES
#define AUDIO_BLOCK_SAMPLES  128
#endif

#ifndef AUDIO_SAMPLE_RATE_EXACT
#define AUDIO_SAMPLE_RATE_EXACT 44100.0f
#endif

#define AUDIO_SAMPLE_RATE AUDIO_SAMPLE_RATE_EXACT

#define noAUDIO_DEBUG_CLASS // disable this class by default

#ifndef __ASSEMBLER__
class m_audio_stream;
class m_audio_connection;
#if defined(AUDIO_DEBUG_CLASS)
class m_AudioDebug;  // for testing only, never for public release
#endif // defined(AUDIO_DEBUG_CLASS)

typedef struct m_audio_block_struct
{
	uint8_t  ref_count;
	uint8_t  reserved1;
	uint16_t memory_pool_index;
	int16_t  data[AUDIO_BLOCK_SAMPLES];
} m_audio_block_t;

class m_audio_connection
{
public:
	m_audio_connection(){}
	m_audio_connection(m_audio_stream &source, m_audio_stream &destination)
		: m_audio_connection() { connect(source,destination); }
	m_audio_connection(m_audio_stream &source, unsigned char sourceOutput,
		m_audio_stream &destination, unsigned char destinationInput)
		: m_audio_connection() { connect(source,sourceOutput, destination,destinationInput); }
	friend class m_audio_stream;
	~m_audio_connection(); 
	int disconnect(void);
	int connect(void);
	int connect(m_audio_stream &source, m_audio_stream &destination) {return connect(source,0,destination,0);};
	int connect(m_audio_stream &source, unsigned char sourceOutput,
		m_audio_stream &destination, unsigned char destinationInput);

	m_audio_stream* src;	// can't use references as... 
	m_audio_stream* dst;	// ...they can't be re-assigned!
	unsigned char src_index;
	unsigned char dest_index;
	m_audio_connection *next_dest; // linked list of connections from one source
	bool isConnected;
#if defined(AUDIO_DEBUG_CLASS)
	friend class m_AudioDebug;
#endif // defined(AUDIO_DEBUG_CLASS)
};

void m_audio_connection_void_constructor(m_audio_connection *conn);


#define m_AudioMemory(num) ({ \
	static DMAMEM m_audio_block_t data[num]; \
	initialize_memory(data, num); \
})

#define CYCLE_COUNTER_APPROX_PERCENT(n) (((float)((uint32_t)(n) *6400u) *(float)(AUDIO_SAMPLE_RATE_EXACT / AUDIO_BLOCK_SAMPLES)) / (float)(F_CPU_ACTUAL))

#define m_AudioProcessorUsage() 		(CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles_total))
#define m_AudioProcessorUsageMax() 		(CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles_total_max))
#define m_AudioProcessorUsageMaxReset() (cpu_cycles_total_max = cpu_cycles_total)
#define m_AudioMemoryUsage() 			(memory_used)
#define m_AudioMemoryUsageMax() 		(memory_used_max)
#define m_AudioMemoryUsageMaxReset() 	(memory_used_max = memory_used)

class m_audio_stream
{
public:
	float processorUsage(void) 			{ return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles); }
	float processorUsageMax(void) 		{ return CYCLE_COUNTER_APPROX_PERCENT(cpu_cycles_max); }
	void  processorUsageMaxReset(void) 	{ cpu_cycles_max = cpu_cycles; }
	bool  isActive(void) 				{ return active; }
	
	uint16_t cpu_cycles;
	uint16_t cpu_cycles_max;
	
	uint8_t numConnections;

	bool active;
	unsigned char num_inputs;
	
	void transmit(m_audio_block_t *block, unsigned char index = 0);
	
	m_audio_block_t *receiveReadOnly(unsigned int index = 0);
	m_audio_block_t *receiveWritable(unsigned int index = 0);
	
	friend void m_software_isr(void);
	friend class m_audio_connection;

	m_audio_connection *destination_list;
	m_audio_block_t **inputQueue;
	
	m_audio_stream *next_update; // for update_all
	
	virtual void update(void) = 0;
};

/* Functions */

void initialize_memory(m_audio_block_t *data, unsigned int num);

void m_audio_stream_constructor(m_audio_stream *stream, unsigned char ninput, m_audio_block_t **iqueue);

void update_all();

bool update_setup();
void update_stop();

m_audio_block_t *allocate_block();
void release_block(m_audio_block_t *block);

void m_software_isr();

#endif // __ASSEMBLER__
#endif // m_audio_stream_h
