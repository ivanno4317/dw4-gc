#define MATH_INLINE
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"
#include "fdlibm.h"

MATH_INLINE double sqrt(double __x)
{
    return __ieee754_sqrt((double)__x);
}