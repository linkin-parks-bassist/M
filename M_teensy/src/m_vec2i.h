#ifndef M_VEC2I_H_
#define M_VEC2I_H_

typedef struct
{
	int16_t x, y;
} vec2i;

#define DISCONNECTED ((vec2i){-1, -1})

#define INPUT_NODE_X		-1
#define INPUT_NODE_Y		 0

#define OUTPUT_NODE_X		 0
#define OUTPUT_NODE_Y		-1

#define INPUT_NODE_COORD  	(vec2i){ INPUT_NODE_X,  INPUT_NODE_Y}
#define OUTPUT_NODE_COORD 	(vec2i){OUTPUT_NODE_X, OUTPUT_NODE_Y}

#define ERROR_COORD			((vec2i){-1, -2})

#endif
