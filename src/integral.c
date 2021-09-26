
#include "integral.h"

static double lfn(double x, linear_fn_t f)
{
    return f.s * x + f.o;
}

double integral_midpnt(linear_fn_t lf, interval_t li)
{
    const double dhl = li.h - li.l;
    const double shl = li.l + li.h;
    return fabs(dhl * lfn(shl / INTEG_TWO, lf));
}

double integral_trapez(linear_fn_t lf, interval_t li)
{
    const double dhl = li.h - li.l;
    const double yl = lfn(li.l, lf);
    if (lf.s == 0.0)
        return fabs(dhl * yl);
    const double dy = lfn(li.h, lf) - yl;
    return fabs(yl * dhl + (dhl * dy / INTEG_TWO));
}

polynomial_item_t integral_factory_riemann(polynomial_t *p, interval_t li, polynomial_item_t n)
{
    polynomial_item_t i, xi, sum = 0;
    const polynomial_item_t dx = (li.h - li.l) / n;
    for (i = 0; i < n; i++)
    {
        xi = li.l + i * dx;
        sum += polynomial_calc(xi, p) * dx;
    }
    return sum;
}

polynomial_item_t integral_factory_midpnt(polynomial_t *p, interval_t li)
{
    const polynomial_item_t dhl = li.h - li.l;
    const polynomial_item_t shl = li.l + li.h;
    return fabs(dhl * polynomial_calc(shl / INTEG_TWO, p));
}

polynomial_item_t integral_factory(polynomial_t *p, interval_t li, polynomial_item_t n)
{
    if (p->order < 2)
        return integral_factory_midpnt(p, li);
    return integral_factory_riemann(p, li, n);
}