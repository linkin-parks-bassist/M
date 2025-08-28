#include "M.h"
#include "m_globals.h"

void m_audio_stream_constructor(m_audio_stream *stream, unsigned char ninput, m_audio_block_t **iqueue)
{
	if (!stream) return;
	
	stream->num_inputs = ninput;
	stream->inputQueue = iqueue;
	
	stream->active = false;
	stream->destination_list = NULL;
	
	for (int i = 0; i < stream->num_inputs; i++)
		stream->inputQueue[i] = NULL;
	
	// add to a simple list, for update_all
	// TODO: replace with a proper data flow analysis in update_all
	if (first_update == NULL)
	{
		first_update = stream;
	}
	else
	{
		m_audio_stream *p;
		
		for (p = first_update; p->next_update; p = p->next_update) ;
		
		p->next_update = stream;
	}
	
	stream->next_update = NULL;
	stream->cpu_cycles = 0;
	stream->cpu_cycles_max = 0;
	stream->numConnections = 0;
}

// Constructor with no parameters: leave unconnected
void m_audio_connection_void_constructor(m_audio_connection *conn)
{
	if (!conn) return;
	
	conn->src = NULL;
	conn->dst = NULL;
	conn->src_index = 0;
	conn->dest_index = 0;
	conn->isConnected = false;
	
	// we are unused right now, so
	// link ourselves at the start of the unused list
	conn->next_dest = unused_connections;
	unused_connections = conn;
}
