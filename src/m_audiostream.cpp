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

#include <Arduino.h>
#include "M.h"

// Transmit an audio data block
// to all streams that connect to an output.  The block
// becomes owned by all the recepients, but also is still
// owned by this object.  Normally, a block must be released
// by the caller after it's transmitted.  This allows the
// caller to transmit to same block to more than 1 output,
// and then release it once after all transmit calls.
void m_audio_stream::transmit(m_audio_block_int *block, unsigned char index)
{
	for (m_audio_connection *c = destination_list; c != NULL; c = c->next_dest)
	{
		if (c->src_index == index)
		{
			if (c->dst->inputQueue[c->dest_index] == NULL)
			{
				c->dst->inputQueue[c->dest_index] = block;
				block->ref_count++;
			}
		}
	}
}


// Receive block from an input.  The block's data
// may be shared with other streams, so it must not be written
m_audio_block_int *m_audio_stream::receiveReadOnly(unsigned int index)
{
	m_audio_block_int *in;

	if (index >= num_inputs) return NULL;
	in = inputQueue[index];
	inputQueue[index] = NULL;
	return in;
}

// Receive block from an input.  The block will not
// be shared, so its contents may be changed.
m_audio_block_int *m_audio_stream::receiveWritable(unsigned int index)
{
	m_audio_block_int *in, *p;

	if (index >= num_inputs) return NULL;
	in = inputQueue[index];
	inputQueue[index] = NULL;
	if (in && in->ref_count > 1) {
		p = allocate_block_int();
		if (p) memcpy(p->data, in->data, sizeof(p->data));
		in->ref_count--;
		in = p;
	}
	return in;
}

// Transmit an audio data block
// to all streams that connect to an output.  The block
// becomes owned by all the recepients, but also is still
// owned by this object.  Normally, a block must be released
// by the caller after it's transmitted.  This allows the
// caller to transmit to same block to more than 1 output,
// and then release it once after all transmit calls.
void m_audio_stream_transmit(m_audio_stream *stream, m_audio_block_int *block, unsigned char index)
{
	if (!stream) return;
	
	for (m_audio_connection *c = stream->destination_list; c != NULL; c = c->next_dest)
	{
		if (c->src_index == index)
		{
			if (c->dst->inputQueue[c->dest_index] == NULL)
			{
				c->dst->inputQueue[c->dest_index] = block;
				block->ref_count++;
			}
		}
	}
}


// Receive block from an input.  The block's data
// may be shared with other streams, so it must not be written
m_audio_block_int *m_audio_stream_receive_read_only(m_audio_stream *stream, unsigned int index)
{
	if (!stream) return NULL;
	
	m_audio_block_int *in;

	if (index >= stream->num_inputs)
		return NULL;
	
	in = stream->inputQueue[index];
	stream->inputQueue[index] = NULL;
	return in;
}

// Receive block from an input.  The block will not
// be shared, so its contents may be changed.
m_audio_block_int *m_audio_stream_receive_writable(m_audio_stream *stream, unsigned int index)
{
	if (!stream) return NULL;
	
	m_audio_block_int *in, *p;

	if (index >= stream->num_inputs)
		return NULL;
	
	in = stream->inputQueue[index];
	stream->inputQueue[index] = NULL;
	
	if (in && in->ref_count > 1)
	{
		p = allocate_block_int();
		if (p) memcpy(p->data, in->data, sizeof(p->data));
		in->ref_count--;
		in = p;
	}
	return in;
}

/**************************************************************************************/


// Destructor
m_audio_connection::~m_audio_connection()
{
	m_audio_connection** pp;
	
	disconnect(); // disconnect ourselves: puts us on the unused list
	// Remove ourselves from the unused list
	pp = &unused_connections;
	while (*pp && *pp != this)
		pp = &((*pp)->next_dest);
	if (*pp) // found ourselves
		*pp = next_dest; // remove ourselves from the unused list
}

/**************************************************************************************/
int m_audio_connection::connect()
{
	int result = 1;
	m_audio_connection *p;
	m_audio_connection **pp;
	m_audio_stream* s;

	do 
	{
		if (isConnected) // already connected
		{
			break;
		}
		
		if (!src || !dst) // NULL src or dst - [old] Stream object destroyed
		{
			result = 3;
			break;
		}
			
		if (dest_index >= dst->num_inputs) // input number too high
		{
			result = 2;
			break;
		}
			
		__disable_irq();
		
		// First check the destination's input isn't already in use
		s = first_update; // first m_audio_stream in the stream list
		while (s) // go through all m_audio_stream objects
		{
			p = s->destination_list;	// first patchCord in this stream's list
			while (p)
			{
				if (p->dst == dst && p->dest_index == dest_index) // same destination - it's in use!
				{
					__enable_irq();
					return 4;
				}
				p = p->next_dest;
			}
			s = s->next_update;
		}
		
		// Check we're on the unused list
		pp = &unused_connections;
		while (*pp && *pp != this)
		{
			pp = &((*pp)->next_dest);
		}
		if (!*pp) // never found ourselves - fail
		{
			result = 5;
			break;
		}
			
		// Now try to add this connection to the source's destination list
		p = src->destination_list; // first m_audio_connection
		if (p == NULL) 
		{
			src->destination_list = this;
		} 
		else 
		{
			while (p->next_dest)  // scan source Stream's connection list for duplicates
			{
				
				if (&p->src == &this->src && &p->dst == &this->dst
					&& p->src_index == this->src_index && p->dest_index == this->dest_index) 
				{
					//Source and destination already connected through another connection, abort
					__enable_irq();
					return 6;
				}
				p = p->next_dest;
			}			
			
			p->next_dest = this; // end of list, can link ourselves in
		}
		
		*pp = next_dest;  // remove ourselves from the unused list
		next_dest = NULL; // we're last in the source's destination list
		
		src->numConnections++;
		src->active = true;

		dst->numConnections++;
		dst->active = true;

		isConnected = true;
		
		result = 0;
	} while (0);
	
	__enable_irq();
	
	return result;
}


int m_audio_connection::connect(m_audio_stream &source, unsigned char sourceOutput,
		m_audio_stream &destination, unsigned char destinationInput)
{
	int result = 1;
	
	if (!isConnected)
	{
		src = &source;
		dst = &destination;
		src_index = sourceOutput;
		dest_index = destinationInput;
		
		result = connect();
	}
	return result;
}

int m_audio_connection::disconnect()
{
	m_audio_connection *p;

	if (!isConnected) return 1;
	if (dest_index >= dst->num_inputs) return 2; // should never happen!
	__disable_irq();
	
	// Remove destination from source list
	p = src->destination_list;
	if (p == NULL)
	{
		//>>> PAH re-enable the IRQ
		__enable_irq();
		return 3;
	}
	else if (p == this)
	{
		if (p->next_dest)
			src->destination_list = next_dest;
		else
			src->destination_list = NULL;
	}
	else
	{
		while (p)
		{
			if (p->next_dest == this) // found the parent of the disconnecting object
			{
				p-> next_dest = this->next_dest; // skip parent's link past us
				break;
			}
			else
			{
				p = p->next_dest; // carry on down the list
			}
		}
	}
	
	//>>> PAH release the audio buffer properly
	//Remove possible pending src block from destination
	if(dst->inputQueue[dest_index] != NULL)
	{
		release_block_int(dst->inputQueue[dest_index]);
		// release_block_int() re-enables the IRQ. Need it to be disabled a little longer
		__disable_irq();
		dst->inputQueue[dest_index] = NULL;
	}

	//Check if the disconnected m_audio_stream objects should still be active
	src->numConnections--;
	if (src->numConnections == 0)
		src->active = false;

	dst->numConnections--;
	if (dst->numConnections == 0)
		dst->active = false;
	
	isConnected 		= false;
	next_dest 			= unused_connections;
	unused_connections  = this;

	__enable_irq();
	
	return 0;
}
