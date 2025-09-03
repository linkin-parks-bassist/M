#ifndef M_BIQUAD_H_
#define M_BIQUAD_H_

typedef struct
{
	int type;
	
	float a0, a1, a2, a3, a4;
    float x1, x2, y1, y2;
} m_trans_biquad_data;

#endif
