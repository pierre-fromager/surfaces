
#include "integral.h"

polynomial_item_t integral_poly_midpnt(polynomial_t *p, interval_t il)
{
    const polynomial_item_t dhl = il.h - il.l;
    const polynomial_item_t shl = il.l + il.h;
    return dhl * polynomial_calc(shl / INTEG_TWO, p);
}

polynomial_item_t integral_poly_trapez(polynomial_t *p, interval_t il)
{
    const polynomial_item_t dhl = il.h - il.l;
    const polynomial_item_t yl = polynomial_calc(il.l, p);
    if (polynomial_getfactor(1, p) == 0.0f)
        return dhl * yl;
    const polynomial_item_t dy = polynomial_calc(il.h, p) - yl;
    return yl * dhl + (dhl * dy / INTEG_TWO);
}

polynomial_item_t integral_poly_simpson(polynomial_t *p, interval_t il)
{
    const polynomial_item_t dx = (il.h - il.l) / 6;
    const polynomial_item_t mid = (il.h + il.l) / INTEG_TWO;
    const polynomial_item_t fl = polynomial_calc(il.l, p);
    const polynomial_item_t fm = polynomial_calc(mid, p);
    const polynomial_item_t fh = polynomial_calc(il.h, p);
    return (fl + 4 * fm + fh) * dx;
}
/*
static polynomial_item_t integral_poly_riemann_rect(polynomial_t *p, interval_t il, polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 0; i < n; i++)
        sum += polynomial_calc(il.l + i * dx, p) * dx;
    return sum;
}*/

static polynomial_item_t integral_poly_riemann_trap(polynomial_t *p, interval_t il, polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 0; i < n; i++)
    {
        const polynomial_item_t term1 = il.l + (i * dx);
        const polynomial_item_t y1 = polynomial_calc(term1, p);
        const polynomial_item_t term2 = il.l + ((i + 1) * dx);
        const polynomial_item_t y2 = polynomial_calc(term2, p);
        sum += 0.5f * dx * (y1 + y2);
    }
    return sum;
}

polynomial_item_t integral_poly_riemann(polynomial_t *p, interval_t il, polynomial_item_t n)
{
    //polynomial_item_t i;
    //polynomial_item_t i = integral_poly_riemann_rect(p, il, n);
    //printf("SUM integral_poly_riemann_rect = %Lf", i);
    return integral_poly_riemann_trap(p, il, n);
}

polynomial_item_t integral_poly_newton_cote_1_2(polynomial_t *p, interval_t il)
{
    const polynomial_item_t dhl = il.h - il.l;
    const polynomial_item_t shl = il.h + il.l;
    const polynomial_item_t fshl = polynomial_calc(shl / INTEG_TWO, p);
    const polynomial_item_t fact = 24.0f;
    polynomial_t *d1;
    d1 = malloc(sizeof(polynomial_t));
    polynomial_construct(p->order - 1, d1);
    derivative_derivate(p, d1);
    const polynomial_item_t d1l = polynomial_calc(il.l, d1);
    const polynomial_item_t d1h = polynomial_calc(il.h, d1);
    polynomial_destruct(d1);
    return (dhl / fact) * ((fact * fshl) + (dhl * (d1h - d1l)));
}

polynomial_item_t integral_poly_reference(polynomial_t *p, interval_t il)
{
    polynomial_t *pad;
    pad = malloc(sizeof(polynomial_t));
    derivative_antiderivate(p, pad);
    const polynomial_item_t r = polynomial_calc(il.h, pad) - polynomial_calc(il.l, pad);
    free(pad);
    return r;
}

polynomial_item_t integral_factory(polynomial_t *p, interval_t il)
{
    if (p->order < 2)
        return integral_poly_midpnt(p, il);
    if (p->order < 4)
        return integral_poly_simpson(p, il);
    return integral_poly_reference(p, il);
}