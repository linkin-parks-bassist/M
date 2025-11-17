#include "m_eng.h"

static const char *FNAME = "m_eng_delay_buffer.c";

int init_delay_buffer(m_delay_buffer *buf)
{
	FUNCTION_START();
	
	if (!buf)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	buf->buffers 	= NULL;
	
	buf->valid 		= 0;
	
	buf->pos 		= 0;
	buf->index 		= 0;
	
	buf->n_buffers 			= 0;
	buf->buffer_array_size 	= 0;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int m_delay_buffer_resize_samples(m_delay_buffer *buf, int n_samples)
{
	FUNCTION_START();
	
	if (!buf)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int alloc_failed = 0;
	int array_size;
	float **new_array;
	
	int buffers_needed = (n_samples + AUDIO_BLOCK_SAMPLES - 1) / AUDIO_BLOCK_SAMPLES;
	
	if (buffers_needed < 1)
	{
		if (buf->buffers)
		{
			for (int i = 0; i < buf->n_buffers; i++)
			{
				if (buf->buffers[i])
				{
					release_buffer(buf->buffers[i]);
					buf->buffers[i] = NULL;
				}
			}
			
			m_free(buf->buffers);
			buf->buffers = NULL;
		}
		
		buf->buffer_array_size = 0;
		buf->n_buffers = 0;
		buf->index = 0;
		buf->pos = 0;
		
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	// Nothing to do !
	if (buf->buffers && buffers_needed == buf->n_buffers)
	{
		RETURN_ERR_CODE(NO_ERROR);
	}
	
	// Make a local VLA on the stack, storing all the existing buffer ptrs.
	//
	// For its length, pick the smallest power of 2 no smaller than buffers_needed
	for (array_size = 1; array_size < buffers_needed; array_size *= 2);
	
	float *array[array_size];
	
	// If the new array cannot fit all of the buffers in the old array,
	// free and NULL them, starting at the tail
	
	for (int i = 0; i < buf->n_buffers - array_size; i++)
	{
		release_buffer(buf->buffers[(buf->index + 1 + i) % buf->n_buffers]);
		buf->buffers[(buf->index + 1 + i) % buf->n_buffers] = NULL;
	}
	
	int live_buffers = binary_min(buf->n_buffers, array_size);
	
	// Copy the existing buffer pointers, in reverse order, starting with
	// the head - so that shrinking or extending is more convenient later
	for (int i = 0; i < array_size; i++)
	{
		if (i < live_buffers)
			array[i] = buf->buffers[positive_mod(buf->index - i, buf->n_buffers)];
		else
			array[i] = NULL;
	}
	
	// If the existing pointer array is too small,
	// unfortunately we will simply have to alloc a new one
	// This is why I am using powers of 2 length; fewer allocs
	if (array_size > buf->buffer_array_size)
	{
		new_array = m_alloc(array_size * sizeof(float*));
		
		// If allocation fails, handle it gracefully
		// Or, at least, provide the engine with the
		// chance to do so
		if (!new_array)
		{
			// We haven't actually touched the struct buf. buf->buffers
			// remains intact, and the counters remain valid. However,
			// it does not have the required size. There are no new mallocs
			// to free, and no uninitialised pointers to worry about. Therefore,
			
			buf->valid = 0;
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		// Allocation succeeded; free the old array and put the new in its place
		m_free(buf->buffers);
		buf->buffers = new_array;
		
		// NULL initialise everything, by reflex. Probably not necessary but
		// always better not to have uninitialised pointers lying around
		// they'll find a way to cause a crash if you give them an inch
		for (int i = 0; i < array_size; i++)
			buf->buffers[i] = NULL;
	}
	else if (buf->buffer_array_size > array_size)
	{
		// On the other hand, if buf->buffer_array_size is larger than necessary,
		// then by choice it is at least 2x as large as necessary, so it would
		// pay to shrink it. We can use realloc to shrink; there is no actual
		// malloc involved in shrinking, so it is fairly cheap, and it will not
		// fail. It is prudent to shrink it when it is
		// well over size.
		
		new_array = m_realloc((void*)buf->buffers, array_size * sizeof(float*));
		
		if (!new_array) // I do not expect realloc to fail a shrinking. If it does, treat it as before
		{
			buf->valid = 0;
			RETURN_ERR_CODE(ERR_ALLOC_FAIL);
		}
		
		buf->buffers = new_array;
	}
	
	buf->buffer_array_size = array_size;
	
	// Okay, now we have saved all the buffers locally and ensured that
	// the pointer array in the struct is large enough. Now, do we need
	// to allocate or free any buffers?
	//
	// We can get away with not freeing but it pays to be frugal with
	// memory. What if the user uses a 1s delay, then changes it to
	// 1ms, and later introduces another 1s delay? Enough of this and
	// the whole system would crash due to what should have been
	// water under the bridge. Not on my watch!
	
	if (live_buffers < buffers_needed) // Need to allocate
	{
		// Since we copied the buffer points in reverse order, it is easy!
		
		alloc_failed = 0;
		for (int i = 0; i < buffers_needed - live_buffers; i++)
		{
			if (!(array[live_buffers + i] = allocate_buffer()))
			{
				alloc_failed = 1;
				buf->n_buffers = live_buffers + i;
				break;
			}
			
			// Alloc succeeded; full the new buffer with 0s
			for (int j = 0; j < AUDIO_BLOCK_SAMPLES; j++)
				array[live_buffers + i][j] = 0.0f;
		}
	}
	else if (live_buffers > buffers_needed)
	{
		for (int i = buffers_needed; i < live_buffers; i++)
		{
			if (array[i])
			{
				release_buffer(array[i]);
				array[i] = NULL;
			}
		}
	}
	
	if (!alloc_failed)
		buf->n_buffers = buffers_needed;
	
	// Okay! Now we have an array with the correct number of buffers,
	// unless, of course, there was an alloc fail, but...
	// all those needed from the original array has been captured,
	// any others free'd, and the array buf->buffers has sufficient
	// size to store all these.
	//
	// All that remains to do is to copy these pointers to buf->buffers,
	// - in reverse order ! - and set buf->index,buf->buffer_array_size
	// and buf->valid
	
	for (int i = 0; i < buf->buffer_array_size; i++)
	{
		if (i < buf->n_buffers)
			buf->buffers[i] = array[buf->n_buffers - 1 - i];
		else
			buf->buffers[i] = NULL;
	}
	
	// Now, the head was at position buf->index. We copied it locally
	// into index 0. Then we changed the length of the array to
	// buffers_needed, and copied the array back in reverse.
	// Therefore the head now lies at index buf->n_buffers - 1
	
	buf->index = buf->n_buffers - 1;
	
	if (alloc_failed)
	{
		buf->valid = 0;
		RETURN_ERR_CODE(ERR_ALLOC_FAIL);
	}
	
	buf->valid = 1;

	RETURN_ERR_CODE(NO_ERROR);
}

int m_delay_buffer_resize_seconds(m_delay_buffer *buf, float seconds)
{
	FUNCTION_START();
	
	int ret_val = m_delay_buffer_resize_samples(buf, MS_TO_SAMPLES(seconds * 1000.0));
	
	RETURN_ERR_CODE(ret_val);
}


int m_delay_buffer_resize_milliseconds(m_delay_buffer *buf, float ms)
{
	FUNCTION_START();
	
	int ret_val = m_delay_buffer_resize_samples(buf, MS_TO_SAMPLES(ms));
	
	RETURN_ERR_CODE(ret_val);
}


int m_delay_buffer_tick(m_delay_buffer *buf, float new_sample)
{
	FUNCTION_START();
	
	if (!buf)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!buf->buffers || buf->n_buffers == 0)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	// Just make sure everything is in order before dereferencing
	buf->index = positive_mod(buf->index, buf->n_buffers);
	buf->pos   = positive_mod(buf->pos,   AUDIO_BLOCK_SAMPLES);
	
	if (buf->buffers && buf->buffers[buf->index])
		buf->buffers[buf->index][buf->pos] = new_sample;
	
	if (buf->pos + 1 >= AUDIO_BLOCK_SAMPLES)
		buf->index = (buf->index + 1) % buf->n_buffers;
	
	buf->pos = (buf->pos + 1) % AUDIO_BLOCK_SAMPLES;
	
	RETURN_ERR_CODE(NO_ERROR);
}

int m_delay_buffer_advance(m_delay_buffer *buf, float *new_samples, unsigned int n)
{
	FUNCTION_START();
	
	if (!buf || !new_samples)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	int ret_val;
	
	for (int i = 0; i < n; i++)
	{
		if ((ret_val = m_delay_buffer_tick(buf, new_samples[i])) != NO_ERROR)
		{
			RETURN_ERR_CODE(ret_val);
		}
	}
	
	RETURN_ERR_CODE(NO_ERROR);
}

int m_delay_buffer_get_delayed_sample(m_delay_buffer *buf, float *dest, unsigned int delay)
{
	FUNCTION_START();
	
	if (!buf || !dest)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!buf->buffers)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int block_delay = (delay + AUDIO_BLOCK_SAMPLES - buf->pos - 1) / AUDIO_BLOCK_SAMPLES;
	int pos_delay = delay % AUDIO_BLOCK_SAMPLES;
	
	int delayed_index = positive_mod(buf->index - block_delay, buf->n_buffers);
	
	if (!buf->buffers[delayed_index])
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int delayed_pos = positive_mod(buf->pos - pos_delay, AUDIO_BLOCK_SAMPLES);
	
	*dest = buf->buffers[delayed_index][delayed_pos];
	
	RETURN_ERR_CODE(NO_ERROR);
}

float *m_delay_buffer_get_delayed_sample_ptr(m_delay_buffer *buf, unsigned int delay)
{
	FUNCTION_START();
	
	if (!buf)
	{
		RETURN_PTR(NULL);
	}
	
	if (!buf->buffers)
	{
		RETURN_PTR(NULL);
	}
	
	int block_delay = (delay + AUDIO_BLOCK_SAMPLES - buf->pos - 1) / AUDIO_BLOCK_SAMPLES;
	int pos_delay = delay % AUDIO_BLOCK_SAMPLES;
	
	int delayed_index = positive_mod(buf->index - block_delay, buf->n_buffers);
	
	if (!buf->buffers[delayed_index])
	{
		RETURN_PTR(NULL);
	}
	
	int delayed_pos = positive_mod(buf->pos - pos_delay, AUDIO_BLOCK_SAMPLES);
	
	RETURN_PTR(&buf->buffers[delayed_index][delayed_pos]);
}

int m_delay_buffer_get_fractional_delayed_sample(m_delay_buffer *buf, float *dest, float delay)
{
	FUNCTION_START();
	
	if (!buf || !dest)
	{
		RETURN_ERR_CODE(ERR_NULL_PTR);
	}
	
	if (!buf->buffers || buf->n_buffers == 0 || delay < 0.0)
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	float early_sample, late_sample;
	int early_delay = (int)ceilf(delay);
	float fractional_part = delay - (float)(early_delay - 1);
	
	int block_delay_early = (early_delay + AUDIO_BLOCK_SAMPLES - buf->pos - 1) / AUDIO_BLOCK_SAMPLES;
	int pos_delay_early = early_delay % AUDIO_BLOCK_SAMPLES;
	
	int early_delayed_index = positive_mod(buf->index - block_delay_early, buf->n_buffers);
	
	if (!buf->buffers[early_delayed_index])
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	int early_delayed_pos = positive_mod(buf->pos - pos_delay_early, AUDIO_BLOCK_SAMPLES);
	int late_delayed_pos  = positive_mod(early_delayed_pos + 1, AUDIO_BLOCK_SAMPLES);
	
	int late_delayed_index = (early_delayed_index + ((late_delayed_pos < early_delayed_pos) ? 1 : 0)) % buf->n_buffers;
	
	if (!buf->buffers[late_delayed_index])
	{
		RETURN_ERR_CODE(ERR_BAD_ARGS);
	}
	
	early_sample = buf->buffers[early_delayed_index][early_delayed_pos];
	late_sample  = buf->buffers[ late_delayed_index][ late_delayed_pos];
	
	*dest = fractional_part * early_sample + (1.0 - fractional_part) * late_sample;
	
	RETURN_ERR_CODE(NO_ERROR);
}

