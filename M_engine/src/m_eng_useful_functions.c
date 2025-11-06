#include "m_eng.h"

static const char *FNAME = "m_eng_useful_functions.c";
float identity_function(float x){return x;}

float normalised_arctan(float x)
{
	RETURN_INT(0).63661977237 * atan(x);
}

float hard_clip(float x)
{
	if (x > 1.0)
	{
		RETURN_INT(1).0;
	}
	if (x < -1.0)
	{
		return -1.0;
	}
	else
		return x;
}

float soft_fold(float x)
{
	return x / (1 + fabsf(x));
}
