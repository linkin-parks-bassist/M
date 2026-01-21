#ifndef M_ENG_SAMPLE_H_
#define M_ENG_SAMPLE_H_

#ifndef M_ENG_SAMPLE_TYPE
  #define M_ENG_SAMPLE_TYPE F32
#endif

typedef int16_t m_raw_sample_t;

#if M_ENG_SAMPLE_TYPE == F32
    typedef float  m_sample_t;      // internal sample
    typedef float  m_parameter_t;   // param
#elif M_ENG_SAMPLE_TYPE == Q15
    typedef int16_t m_sample_t;     // Q1.15
    typedef int32_t m_parameter_t;  // Q17.15 (for >1 parameters)
#endif


/* ============================================================
   scalar ADD
   ============================================================ */
static inline m_sample_t m_add_sample_sample(m_sample_t x, m_sample_t y)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    float s = x + y;
    if (s > 1.0f) s = 1.0f;
    else if (s < -1.0f) s = -1.0f;
    return s;
  #else
    float xf = x, yf = y, out;
    arm_add_f32(&xf, &yf, &out, 1);
    if (out > 1.0f) out = 1.0f;
    else if (out < -1.0f) out = -1.0f;
    return out;
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    int32_t s = (int32_t)x + (int32_t)y;
    return (m_sample_t)__SSAT(s, 16);
  #else
    m_sample_t out;
    arm_add_q15(&x, &y, &out, 1);
    return out;
  #endif

#endif
}


/* ============================================================
   scalar SUB
   ============================================================ */
static inline m_sample_t m_sub_sample_sample(m_sample_t x, m_sample_t y)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    float d = x - y;
    if (d > 1.0f) d = 1.0f;
    else if (d < -1.0f) d = -1.0f;
    return d;
  #else
    float xf = x, yf = y, out;
    arm_sub_f32(&xf, &yf, &out, 1);
    if (out > 1.0f) out = 1.0f;
    else if (out < -1.0f) out = -1.0f;
    return out;
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    int32_t d = (int32_t)x - (int32_t)y;
    return (m_sample_t)__SSAT(d, 16);
  #else
    m_sample_t out;
    arm_sub_q15(&x, &y, &out, 1);
    return out;
  #endif

#endif
}


/* ============================================================
   scalar MUL sample × sample
   ============================================================ */
static inline m_sample_t m_mul_sample_sample(m_sample_t x, m_sample_t y)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    float p = x * y;
    if (p > 1.0f) p = 1.0f;
    else if (p < -1.0f) p = -1.0f;
    return p;
  #else
    float xf = x, yf = y, out;
    arm_mult_f32(&xf, &yf, &out, 1);
    if (out > 1.0f) out = 1.0f;
    else if (out < -1.0f) out = -1.0f;
    return out;
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    int32_t p = (int32_t)x * (int32_t)y;   // Q30
    p >>= 15;                              // → Q15
    return (m_sample_t)__SSAT(p, 16);
  #else
    m_sample_t out;
    arm_mult_q15(&x, &y, &out, 1);
    return out;
  #endif

#endif
}


/* ============================================================
   scalar MUL param × sample
   m_parameter_t = Q17.15
   m_sample_t    = Q1.15
   ============================================================ */
static inline m_sample_t m_mul_param_sample(m_parameter_t x, m_sample_t y)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    float p = x * y;
    if (p > 1.0f) p = 1.0f;
    else if (p < -1.0f) p = -1.0f;
    return p;
  #else
    float xf = x, yf = y, out;
    arm_mult_f32(&xf, &yf, &out, 1);
    if (out > 1.0f) out = 1.0f;
    else if (out < -1.0f) out = -1.0f;
    return out;
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    int64_t p = (int64_t)x * (int64_t)y;   // Q17.15 × Q1.15 → Q18.30
    p >>= 15;                              // → Q18.15
    return (m_sample_t)__SSAT((int32_t)p, 16);
  #else
    int64_t p = (int64_t)x * (int64_t)y;
    p >>= 15;
    return (m_sample_t)__SSAT((int32_t)p, 16);
  #endif

#endif
}


/* ============================================================
   scalar MUL sample × param
   ============================================================ */
static inline m_sample_t m_mul_sample_param(m_sample_t x, m_parameter_t y)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    float p = x * y;
    if (p > 1.0f) p = 1.0f;
    else if (p < -1.0f) p = -1.0f;
    return p;
  #else
    float xf = x, yf = y, out;
    arm_mult_f32(&xf, &yf, &out, 1);
    if (out > 1.0f) out = 1.0f;
    else if (out < -1.0f) out = -1.0f;
    return out;
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    int64_t p = (int64_t)x * (int64_t)y;   // Q1.15 × Q17.15 → Q18.30
    p >>= 15;                              // → Q18.15
    return (m_sample_t)__SSAT((int32_t)p, 16);
  #else
    int64_t p = (int64_t)x * (int64_t)y;
    p >>= 15;
    return (m_sample_t)__SSAT((int32_t)p, 16);
  #endif

#endif
}


/* ============================================================
   VECTOR ADD
   ============================================================ */
static inline void m_add_samples(m_sample_t *dest, m_sample_t *x, m_sample_t *y, int n)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++) {
        float s = x[i] + y[i];
        if (s > 1.0f) s = 1.0f;
        else if (s < -1.0f) s = -1.0f;
        dest[i] = s;
    }
  #else
    arm_add_f32(x, y, dest, n);
    for (int i = 0; i < n; i++) {
        float s = dest[i];
        if (s > 1.0f) dest[i] = 1.0f;
        else if (s < -1.0f) dest[i] = -1.0f;
    }
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++)
        dest[i] = (m_sample_t)__SSAT((int32_t)x[i] + (int32_t)y[i], 16);
  #else
    arm_add_q15(x, y, dest, n);
  #endif

#endif
}


/* ============================================================
   VECTOR SUB
   ============================================================ */
static inline void m_sub_samples(m_sample_t *dest, m_sample_t *x, m_sample_t *y, int n)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++) {
        float d = x[i] - y[i];
        if (d > 1.0f) d = 1.0f;
        else if (d < -1.0f) d = -1.0f;
        dest[i] = d;
    }
  #else
    for (int i = 0; i < n; i++) {
        float a = x[i], b = y[i], out;
        arm_sub_f32(&a, &b, &out, 1);
        if (out > 1.0f) out = 1.0f;
        else if (out < -1.0f) out = -1.0f;
        dest[i] = out;
    }
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++)
        dest[i] = (m_sample_t)__SSAT((int32_t)x[i] - (int32_t)y[i], 16);
  #else
    arm_sub_q15(x, y, dest, n);
  #endif

#endif
}


/* ============================================================
   VECTOR MUL sample × sample
   ============================================================ */
static inline void m_mul_samples(m_sample_t *dest, m_sample_t *x, m_sample_t *y, int n)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++) {
        float p = x[i] * y[i];
        if (p > 1.0f) p = 1.0f;
        else if (p < -1.0f) p = -1.0f;
        dest[i] = p;
    }
  #else
    arm_mult_f32(x, y, dest, n);
    for (int i = 0; i < n; i++) {
        float p = dest[i];
        if (p > 1.0f) dest[i] = 1.0f;
        else if (p < -1.0f) dest[i] = -1.0f;
    }
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++) {
        int32_t p = (int32_t)x[i] * (int32_t)y[i];
        p >>= 15;
        dest[i] = (m_sample_t)__SSAT(p, 16);
    }
  #else
    arm_mult_q15(x, y, dest, n);
  #endif

#endif
}


/* ============================================================
   VECTOR MUL param × samples
   (Q17.15 × Q1.15)
   ============================================================ */
static inline void m_mul_param_samples(m_sample_t *dest, m_parameter_t x, m_sample_t *y, int n)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++) {
        float p = x * y[i];
        if (p > 1.0f) p = 1.0f;
        else if (p < -1.0f) p = -1.0f;
        dest[i] = p;
    }
  #else
    for (int i = 0; i < n; i++) {
        float xf = x, yf = y[i], out;
        arm_mult_f32(&xf, &yf, &out, 1);
        if (out > 1.0f) out = 1.0f;
        else if (out < -1.0f) out = -1.0f;
        dest[i] = out;
    }
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  /* CMSIS cannot handle Q17.15 parameters. Must be manual. */
  for (int i = 0; i < n; i++) {
      int64_t p = (int64_t)x * (int64_t)y[i];  // Q18.30
      p >>= 15;                                // → Q18.15
      dest[i] = (m_sample_t)__SSAT((int32_t)p, 16);
  }

#endif
}


/* ============================================================
   VECTOR MUL samples × param
   ============================================================ */
static inline void m_mul_samples_param(m_sample_t *dest, m_sample_t *x, m_parameter_t y, int n)
{
#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++)
    {
        float p = x[i] * y;
        if (p > 1.0f) p = 1.0f;
        else if (p < -1.0f) p = -1.0f;
        dest[i] = p;
    }
  #else
    for (int i = 0; i < n; i++)
    {
        float xf = x[i], yf = y, out;
        arm_mult_f32(&xf, &yf, &out, 1);
        if (out > 1.0f) out = 1.0f;
        else if (out < -1.0f) out = -1.0f;
        dest[i] = out;
    }
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

  for (int i = 0; i < n; i++)
  {
      int64_t p = (int64_t)x[i] * (int64_t)y;
      p >>= 15;
      dest[i] = (m_sample_t)__SSAT((int32_t)p, 16);
  }

#endif
}


/* ============================================================
   RAW → INTERNAL sample conversion
   ============================================================ */
static inline void m_convert_raw_samples(m_sample_t *dest, m_raw_sample_t *src, int n)
{
    if (!dest || !src)
        return;

#if M_ENG_SAMPLE_TYPE == F32

  #ifdef NO_CMSIS
    for (int i = 0; i < n; i++)
        dest[i] = (float)src[i] * (1.0f / 32768.0f);
  #else
    arm_scale_f32((float*)src, 1.0f/32768.0f, (float*)dest, n);
  #endif

#elif M_ENG_SAMPLE_TYPE == Q15

    memcpy(dest, src, n * sizeof(m_sample_t));

#endif
}

#endif
