
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

polynomial_item_t integral_poly_newton_cote_1_2(polynomial_t *p, interval_t il)
{
    const polynomial_item_t dhl = il.h - il.l;
    const polynomial_item_t shl = il.h + il.l;
    const polynomial_item_t fshl = polynomial_calc(shl / INTEG_TWO, p);
    const polynomial_item_t fact = 24.0f;
    polynomial_t *d1;
    d1 = (polynomial_t *)malloc(sizeof(polynomial_t));
    polynomial_construct(p->order - 1, d1);
    derivative_derivate(p, d1);
    const polynomial_item_t d1l = polynomial_calc(il.l, d1);
    const polynomial_item_t d1h = polynomial_calc(il.h, d1);
    polynomial_destruct(d1);
    free(d1);
    return (dhl / fact) * ((fact * fshl) + (dhl * (d1h - d1l)));
}

polynomial_item_t integral_poly_reference(polynomial_t *p, interval_t il)
{
    polynomial_t *pad;
    polynomial_item_t r;
    pad = (polynomial_t *)malloc(sizeof(polynomial_t));
    derivative_antiderivate(p, pad);   
    r = polynomial_calc(il.h, pad) - polynomial_calc(il.l, pad);
    polynomial_destruct(pad);
    free(pad);
    return r;
}

void integral_poly_reference_gmp(mpz_t acc, polynomial_t *p, interval_t il)
{
    polynomial_t *pad;
    const mp_bitcnt_t precision = 64;
    mpz_t ht, lt;
    pad = (polynomial_t *)malloc(sizeof(polynomial_t));
    derivative_antiderivate(p, pad);
    mpz_init2(ht, precision);
    mpz_init2(lt, precision);
    polynomial_calc_gmp_int(lt, (polynomial_item_t)il.l, pad);
    polynomial_calc_gmp_int(ht, il.h, pad);
    mpz_sub(acc, ht, lt);
    polynomial_destruct(pad);
    free(pad);
    mpz_clear(ht);
    mpz_clear(lt);
}

polynomial_item_t integral_factory_riemann(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n,
    integral_riemann_method_t m)
{
    switch (m)
    {
    case riemann_middle_point:
        return riemann_sum_mp(p, il, n);
        break;

    case riemann_trapezoid:
        return riemann_sum_trap(p, il, n);
        break;

    case riemann_rectangle:
        return riemann_sum_rect(p, il, n);
        break;

    case riemann_left:
        return riemann_sum_left(p, il, n);
        break;

    case riemann_right:
        return riemann_sum_right(p, il, n);
        break;

    default:
        break;
    }

    return 0;
}

void integral_factory(polynomial_t *p, interval_t il, char *result)
{
    const char *resfmt = (p->order < 48) ? "%Lf" : "%Zd";
    const size_t ressize = sizeof(char) * INTEG_FACTORY_BUF_SIZE;
    const mp_bitcnt_t precision = 64;
    mpz_t acc;
    if (p->order < 2)
    {        
        snprintf(result,ressize, resfmt, integral_poly_midpnt(p, il));
        return;
    }
    if (p->order < 4)
    {
        snprintf(result, ressize, resfmt, integral_poly_simpson(p, il));
        return;
    }
    if (p->order < 48)
    {
        snprintf(result, ressize, resfmt, integral_poly_reference(p, il));
        return;
    }    
    mpz_init2(acc, precision);
    integral_poly_reference_gmp(acc, p, il);
    gmp_sprintf(result, resfmt, acc);
    mpz_clear(acc);
    return;
}