#ifndef M_ENG_DELAY_BUFFER_H_
#define M_ENG_DELAY_BUFFER_H_

typedef struct
{
	int valid;
	
	int pos;
	int index;
	
	int n_buffers;
	int buffer_array_size;
	float **buffers;
} m_delay_buffer;

int init_delay_buffer(m_delay_buffer *buf);

int m_delay_buffer_resize_samples(m_delay_buffer *buf, int n_samples);
int m_delay_buffer_resize_seconds(m_delay_buffer *buf, float seconds);
int m_delay_buffer_resize_milliseconds(m_delay_buffer *buf, float ms);

int m_delay_buffer_tick(m_delay_buffer *buf, float new_sample);
int m_delay_buffer_advance(m_delay_buffer *buf, float *new_samples, unsigned int n);

int m_delay_buffer_get_delayed_sample(m_delay_buffer *buf, float *dest, unsigned int delay);
float *m_delay_buffer_get_delayed_sample_ptr(m_delay_buffer *buf, unsigned int delay);
int m_delay_buffer_get_fractional_delayed_sample(m_delay_buffer *buf, float *dest, float delay);

#endif
