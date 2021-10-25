
#include "polynomial.h"

void polynomial_construct(polynomial_order_t o, polynomial_t *p)
{
    const unsigned nbelt = (o + 2);
    const size_t poasize = sizeof(polynomial_order_t) * nbelt;
    const size_t piasize = sizeof(polynomial_item_t) * nbelt;
    const size_t prasize = sizeof(polynomial_ratio_t) * nbelt;
    p->order = o;
    p->orders = (polynomial_order_t *)malloc(poasize);
    p->factors = (polynomial_item_t *)malloc(piasize);
    p->fratios = (polynomial_ratio_t *)malloc(prasize);
    polynomial_reset(p);
}

void polynomial_reset(polynomial_t *p)
{
    polynomial_order_t ocpt;
    const polynomial_item_t ifactor = 0;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        *(p->orders + ocpt) = ocpt;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        *(p->factors + ocpt) = ifactor;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        *(p->fratios + ocpt) = (polynomial_ratio_t){.num = ifactor, .denom = 1};
}

void polynomial_destruct(polynomial_t *p)
{
    free(p->fratios);
    free(p->factors);
    free(p->orders);
}

void polynomial_setfactor(polynomial_order_t o, polynomial_item_t v, polynomial_t *p)
{
    *(p->factors + o) = v;
}

void polynomial_setratio(polynomial_order_t o, int num, int denom, polynomial_t *p)
{
    *(p->fratios + o) = (polynomial_ratio_t){.num = num, .denom = denom};
}

void polynomial_addratio(polynomial_order_t o, polynomial_ratio_t r, polynomial_t *p)
{
    const polynomial_ratio_t cr = polynomial_getratio(o, p);
    *(p->fratios + o) = fraction_add(cr, r);
}

polynomial_item_t polynomial_getfactor(polynomial_order_t o, polynomial_t *p)
{
    return isnan(*(p->factors + o)) ? 0 : *(p->factors + o);
}

polynomial_item_t polynomial_getorder(polynomial_order_t o, polynomial_t *p)
{
    return *(p->orders + o);
}

polynomial_ratio_t polynomial_getratio(polynomial_order_t o, polynomial_t *p)
{
    const polynomial_ratio_t r = *(p->fratios + o);
    return r;
}

long double _powl(long double f, long double e)
{
    int i;
    long double p;
    if (e == 0)
        return 1;
    if (f == 0 || e == 1)
        return f;
    p = 1;
    for (i = 0; i < e; i++)
        p *= f;
    return p;
}

polynomial_item_t polynomial_calc(polynomial_item_t x, polynomial_t *p)
{
    polynomial_order_t ocpt;
    polynomial_item_t sum = 0;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        if (*(p->factors + ocpt) != 0.0f)
            sum += polynomial_getfactor(ocpt, p) * _powl(x, polynomial_getorder(ocpt, p));
    return sum;
}

void polynomial_calc_gmp_int(mpz_t acc, polynomial_item_t x, polynomial_t *p)
{
    const mp_bitcnt_t precision = 64;
    mpz_t fact, powd, term, xz;
    mpz_init2(acc, precision);
    mpz_init2(fact, precision);
    mpz_init2(term, precision);
    mpz_init2(powd, precision);
    mpz_init2(xz, precision);
    polynomial_order_t ocpt;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        if (polynomial_getratio(ocpt, p).num != 0)
        {
            const polynomial_ratio_t ratio = polynomial_getratio(ocpt, p);
            mpz_init_set_ui(fact, (unsigned long)ratio.num);
            mpz_init_set_ui(xz, (unsigned long)x);
            const unsigned long xo = (unsigned long)polynomial_getorder(ocpt, p);
            mpz_pow_ui(powd, xz, xo);
            mpz_mul(term, fact, powd);
            mpz_div_ui(term, term, (unsigned long)ratio.denom);
            mpz_add(acc, acc, term);
        }
    mpz_clear(fact);
    mpz_clear(powd);
    mpz_clear(term);
    mpz_clear(xz);
}
