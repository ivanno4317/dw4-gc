#define MATH_INLINE
#include "math_api.h"
#include "fdlibm.h"

MATH_INLINE double sqrt(double __x)
{
    return __ieee754_sqrt((double)__x);
}

MATH_INLINE float cosf(float __x)
{
    return cos((double)__x);
}

MATH_INLINE float powf(float __x, float __y)
{
    return pow((double)__x, (double)__y);
}