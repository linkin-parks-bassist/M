#include "m_eng.h"

static const char *FNAME = "m_printf.c";

#ifdef ALLOW_PRINTLINES
static uint64_t voice_print_mask = (uint64_t)((int64_t)(-1));
#else
static uint64_t voice_print_mask = 0;
#endif

void m_printf(const char *fmt, ...)
{
	#ifdef ALLOW_PRINTLINES
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	
	#ifndef M_SIMULATED
	Serial.print(buf);
	Serial.flush();
	#else
	fputs(buf, stdout);
	#endif
	#endif
}

const char *voice_colour_table[64] = {"\e[31m",
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[33m", 
	"\e[34m", "\e[35m", "\e[36m", "\e[33m", "\e[34m", "\e[35m", "\e[36m"
};

void m_voice_printf(int who, const char *fmt, ...)
{
	if (voice_print_mask & (1 << who))
	{
		char buf[1024];
		va_list args;
		int index = snprintf(buf, 7, "%s", voice_colour_table[who]);
		va_start(args, fmt);
		index += vsnprintf(&buf[index], sizeof(buf) - index, fmt, args);
		snprintf(&buf[index], sizeof(buf) - index, "\e[0m");
		va_end(args);
		#ifndef M_SIMULATED
		Serial.print(buf);
		Serial.flush();
		#else
		fputs(buf, stdout);
		#endif
	}
}

void m_mute_voice(int who)
{
	voice_print_mask &= ~(1 << who);
}

void m_unmute_voice(int who)
{
	voice_print_mask |= (1 << who);
}

void serial_print_blocks(int n, ...)
{
	char buf[4096];
	char sub_buf[64];
	int pos = 0;
	
	va_list args;
	va_start(args, n);
	float *blocks[n];
	for (int j = 0; j < n; j++)
		blocks[j] = va_arg(args, float*);
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sprintf(sub_buf, "%6f ", blocks[j][i]);
			sprintf(&buf[pos], sub_buf);
			pos += strlen(sub_buf);
		}
		sprintf(&buf[pos], "\n");
		pos++;
	}
	va_end(args);
	#ifndef M_SIMULATED
	Serial.print(buf);
	#else
	fputs(buf, stdout);
	#endif
}

void pretty_print_block(int16_t *data, const char *start)
{
	char buf[1024];
	char sub_buf[128];
	int16_t abs;
	int len, j;
	int pos = 0;
	
	#define SPACING 7
	
	if (start)
	{
		sprintf(buf, start);
		pos = strlen(buf);
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (i % 32 == 0)
		{
			buf[pos++] = '\n';
			sprintf(&buf[pos], "%d:  ", i);
			
			pos += 2;
			
			if (i < 10)
			{
				pos++;
				buf[pos++] = ' ';
			}
			else if (i < 100)
			{
				pos++;
				buf[pos++] = ' ';
			}
		}
		
		if (data[i] < 0)
		{
			sub_buf[0] = '-';
			abs = -data[i];
		}
		else
		{
			sub_buf[0] = ' ';
			abs = data[i];
		}
		sprintf(&sub_buf[1], "%d", abs);
		
		
		len = strlen(sub_buf);
		
		for (j = 0; j < len; j++)
			buf[pos++] = sub_buf[j];
		
		while (j < SPACING)
		{
			buf[pos++] = ' ';
			j++;
		}
	}
	
	buf[pos++] = '\n';
	buf[pos++] = '\n';
	buf[pos] = 0;
	
	m_printf(buf);
}

void pretty_print_block_float(float *data, const char *start)
{
	char buf[1024];
	char sub_buf[128];
	float abs;
	int len, j;
	int pos = 0;
	
	#define SPACING 7
	
	if (start)
	{
		sprintf(buf, start);
		pos = strlen(buf);
	}
	
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
	{
		if (i % 32 == 0)
		{
			buf[pos++] = '\n';
			sprintf(&buf[pos], "%d:  ", i);
			
			pos += 2;
			
			if (i < 10)
			{
				pos++;
				buf[pos++] = ' ';
			}
			else if (i < 100)
			{
				pos++;
				buf[pos++] = ' ';
			}
		}
		
		if (data[i] < 0)
		{
			sub_buf[0] = '-';
			abs = -data[i];
		}
		else
		{
			sub_buf[0] = ' ';
			abs = data[i];
		}
		sprintf(&sub_buf[1], "%d", (int)(32768.0 * abs));
		
		
		len = strlen(sub_buf);
		
		for (j = 0; j < len; j++)
			buf[pos++] = sub_buf[j];
		
		while (j < SPACING)
		{
			buf[pos++] = ' ';
			j++;
		}
	}
	
	buf[pos++] = '\n';
	buf[pos++] = '\n';
	buf[pos] = 0;
	
	m_printf(buf);
}
