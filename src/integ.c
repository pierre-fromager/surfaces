
#include "integ.h"

static double lfn(double x, linear_fn_t f)
{
    return f.s * x + f.o;
}

double integ_trapezoid(linear_fn_t lf, interval_t li)
{
    const double dhl = li.h - li.l;
    const double yl = lfn(li.l, lf);
    if (lf.s == 0.0)
        return fabs(dhl * yl);
    const double dy = lfn(li.h, lf) - yl;
    return fabs(yl * dhl + (dhl * dy / 2));
}
