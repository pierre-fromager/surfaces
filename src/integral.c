
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

polynomial_item_t integral_poly_simpson(polynomial_t *p, interval_t li)
{
    const polynomial_item_t dx = (li.h - li.l) / 6;
    const polynomial_item_t mid = (li.h + li.l) / 2;
    const polynomial_item_t fl = polynomial_calc(li.l, p);
    const polynomial_item_t fm = polynomial_calc(mid, p);
    const polynomial_item_t fh = polynomial_calc(li.h, p);
    return (fl + 4 * fm + fh) * dx;
}

polynomial_item_t integral_poly_riemann(polynomial_t *p, interval_t li, polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (li.h - li.l) / n;
    for (i = 0; i < n; i++)
        sum += polynomial_calc(li.l + i * dx, p) * dx;
    return sum;
}

polynomial_item_t integral_poly_midpnt(polynomial_t *p, interval_t li)
{
    const polynomial_item_t dhl = li.h - li.l;
    const polynomial_item_t shl = li.l + li.h;
    return fabs(dhl * polynomial_calc(shl / INTEG_TWO, p));
}

polynomial_item_t integral_poly_newton_cote_1_2(polynomial_t *p, interval_t li)
{
    const polynomial_item_t dhl = li.h - li.l;
    const polynomial_item_t shl = li.h + li.l;
    const polynomial_item_t fact = 24.0f;
    polynomial_t *d1;
    d1 = malloc(sizeof(polynomial_t));
    polynomial_construct(p->order - 1, d1);
    derivative_derivate(p, d1);
    const polynomial_item_t d1l = polynomial_calc(li.l, d1);
    const polynomial_item_t d1h = polynomial_calc(li.h, d1);
    polynomial_destruct(d1);
    return (dhl / fact) * (fact * polynomial_calc(shl / 2.0f, p) + (dhl * (d1h - d1l)));
}

polynomial_item_t integral_poly_newton_cote_2_2(polynomial_t *p, interval_t li)
{
    const polynomial_item_t dhl = li.h - li.l;
    const polynomial_item_t fact = 12.0f;
    const polynomial_item_t dfact = dhl / fact;
    const polynomial_item_t hfact = fact / 2.0f;
    const polynomial_item_t fl = polynomial_calc(li.l, p);
    const polynomial_item_t fh = polynomial_calc(li.h, p);
    polynomial_t *d1;
    d1 = malloc(sizeof(polynomial_t));
    polynomial_construct(p->order - 1, d1);
    derivative_derivate(p, d1);
    const polynomial_item_t d1l = polynomial_calc(li.l, d1);
    const polynomial_item_t d1h = polynomial_calc(li.h, d1);
    polynomial_destruct(d1);
    return dfact * (hfact * (fl + fh)) + (dhl * (d1h - d1l));
}

polynomial_item_t integral_factory(polynomial_t *p, interval_t li, polynomial_item_t n)
{
    if (p->order < 2)
        return integral_poly_midpnt(p, li);
    if (p->order < 4)
        return integral_poly_simpson(p, li);
    return integral_poly_riemann(p, li, n);
}