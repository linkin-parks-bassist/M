#ifndef M_ENG_FLOPS_H_
#define M_ENG_FLOPS_H_

#ifndef RESTRICT
#  if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define RESTRICT restrict
#  elif defined(__GNUC__) || defined(__clang__)
#    define RESTRICT __restrict__
#  else
#    define RESTRICT
#  endif
#endif

static inline void m_add_f32(float *dest, float *RESTRICT x, float *RESTRICT y, uint32_t n)
{
	if (dest && x && y)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i    ] = x[i    ] + y[i    ];
			dest[i + 1] = x[i + 1] + y[i + 1];
			dest[i + 2] = x[i + 2] + y[i + 2];
			dest[i + 3] = x[i + 3] + y[i + 3];
		}
		for (; i < n; i++) dest[i] = x[i] + y[i];
		#else
		arm_add_f32(x, y, dest, n);
		#endif
	}
}

static inline void m_sub_f32(float *dest, float *RESTRICT x, float *RESTRICT y, uint32_t n)
{
	if (dest && x && y)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i    ] = x[i    ] - y[i    ];
			dest[i + 1] = x[i + 1] - y[i + 1];
			dest[i + 2] = x[i + 2] - y[i + 2];
			dest[i + 3] = x[i + 3] - y[i + 3];
		}
		for (; i < n; i++) dest[i] = x[i] - y[i];
		#else
		arm_sub_f32(x, y, dest, n);
		#endif
	}
}


static inline void m_add_to_f32(float *dest, float *x, uint32_t n)
{
	if (dest && x)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i    ] += x[i    ];
			dest[i + 1] += x[i + 1];
			dest[i + 2] += x[i + 2];
			dest[i + 3] += x[i + 3];
		}
		for (; i < n; i++) dest[i] += x[i];
		#else
		arm_add_f32(dest, x, dest, n);
		#endif
	}
}

static inline void m_sub_from_f32(float *dest, float *x, uint32_t n)
{
	if (dest && x)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i    ] -= x[i    ];
			dest[i + 1] -= x[i + 1];
			dest[i + 2] -= x[i + 2];
			dest[i + 3] -= x[i + 3];
		}
		for (; i < n; i++) dest[i] -= x[i];
		#else
		arm_sub_f32(dest, x, dest, n);
		#endif
	}
}


static inline void m_mul_and_add_f32(float *dest, float *RESTRICT x, float *RESTRICT y, uint32_t n)
{
	if (dest && x && y)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i]     += x[i]     * y[i];
			dest[i + 1] += x[i + 1] * y[i + 1];
			dest[i + 2] += x[i + 2] * y[i + 2];
			dest[i + 3] += x[i + 3] * y[i + 3];
		}
		for (; i < n; i++) dest[i] += x[i] * y[i];
		#else
		float temp[n];
		arm_mult_f32(x, y, temp, n);
		arm_add_f32(dest, temp, dest, n);
		#endif
	}
}

static inline void m_scale_and_add_to_f32(float *RESTRICT dest, float *RESTRICT x, float s, uint32_t n)
{
	if (dest && x)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i]     += x[i]     * s;
			dest[i + 1] += x[i + 1] * s;
			dest[i + 2] += x[i + 2] * s;
			dest[i + 3] += x[i + 3] * s;
		}
		for (; i < n; i++) dest[i] += x[i] * s;
		#else
		float temp[n];
		arm_scale_f32(x, s, temp, n);
		arm_add_f32(dest, temp, dest, n);
		#endif
	}
}


static inline void m_scale_f32(float *dest, float *x, float s, uint32_t n)
{
	if (dest && x)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			dest[i]      = x[i]     * s;
			dest[i + 1]  = x[i + 1] * s;
			dest[i + 2]  = x[i + 2] * s;
			dest[i + 3]  = x[i + 3] * s;
		}
		for (; i < n; i++) dest[i] = x[i] * s;
		#else
		arm_scale_f32(x, s, dest, n);
		#endif
	}
}

static inline void m_scale_in_place_f32(float *x, float s, uint32_t n)
{
	if (x)
	{
		#ifdef NO_CMSIS
		int i = 0;
		for (; i + 3 < n; i += 4)
		{
			x[i    ] *= s;
			x[i + 1] *= s;
			x[i + 2] *= s;
			x[i + 3] *= s;
		}
		for (; i < n; i++) x[i] *= s;
		#else
		arm_scale_f32(x, s, x, n);
		#endif
	}
}

#endif
