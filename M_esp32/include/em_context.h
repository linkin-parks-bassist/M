#ifndef M_ESP32_CONTEXT_H_
#define M_ESP32_CONTEXT_H_

typedef struct
{
	teensy_context teensy;
} esp32_context;

extern esp32_context global_cxt;

int init_esp32_context(esp32_context *cxt);

#endif
