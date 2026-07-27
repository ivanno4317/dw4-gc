#include "fdlibm.h"
#include "math_api.h"
static const double

    two54
    = 1.80143985094819840000e+16,       
    twom54 = 5.55111512312578270212e-17,
    big = 1.0e+300, tiny = 1.0e-300;

double ldexp(double x, int n)
{
	s32 k, hx, lx;
	if (!isfinite(x) || x == 0.0)
		return x;

	hx = __HI(x);
	lx = __LO(x);
	k  = (hx & 0x7ff00000) >> 20;
	if (k == 0) {                
		if ((lx | (hx & 0x7fffffff)) == 0)
			return x;
		x *= two54;
		hx = __HI(x);
		k  = ((hx & 0x7ff00000) >> 20) - 54;
		if (n < -50000)
			return tiny * x;
	}
	if (k == 0x7ff)
		return x + x;
	k = k + n;
	if (k > 0x7fe)
		return big * copysign(big, x);
	if (k > 0)                        
	{
		__HI(x) = (hx & 0x800fffff) | (k << 20);
		return x;
	}
	if (k <= -54)
		if (n > 50000)                    
			return big * copysign(big, x);
		else
			return tiny * copysign(tiny, x);
	k += 54;                                
	__HI(x) = (hx & 0x800fffff) | (k << 20);
	return x * twom54;
}
