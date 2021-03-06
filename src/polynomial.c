
#include "polynomial.h"

void polynomial_construct(polynomial_order_t o, polynomial_t *p)
{
    p->order = o;    
    const size_t pca = (p->order + 3);// (p->order + 3) for polynomial_t alloc
    p->factors = (polynomial_item_t *)malloc(sizeof(polynomial_item_t) * pca);
    p->fratios = (polynomial_ratio_t *)malloc(sizeof(polynomial_ratio_t) * pca);
    polynomial_reset(p);
}

void polynomial_reset(polynomial_t *p)
{
    polynomial_order_t ocpt;
    const polynomial_item_t ifactor = 0;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        *(p->factors + ocpt) = ifactor;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        *(p->fratios + ocpt) = (polynomial_ratio_t){.num = ifactor, .denom = 1};
}

void polynomial_destruct(polynomial_t *p)
{
    free(p->factors);
    free(p->fratios);
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

polynomial_item_t polynomial_gethighestfactor(polynomial_t *p)
{
    polynomial_order_t ocpt;
    polynomial_item_t hf = 0;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
    {
        const polynomial_item_t cf = polynomial_getfactor(ocpt, p);
        hf = (cf > hf) ? cf : hf;
    }
    return hf;
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
            sum += polynomial_getfactor(ocpt, p) * _powl(x, (polynomial_item_t)ocpt);
    return sum;
}

polynomial_order_t polynomial_add(polynomial_t *p1, polynomial_t *p2, polynomial_t *pr)
{
    polynomial_order_t ocpt;
    const unsigned short p1ogt = p1->order > p2->order;
    const polynomial_order_t ho = p1ogt ? p1->order : p2->order;
    const size_t asize = (ho + 1) * sizeof(polynomial_item_t);
    memcpy(pr->factors, (p1ogt) ? p1->factors : p2->factors, asize);
    if (p1ogt)
        for (ocpt = 0; ocpt < (ho + 1); ocpt++)
        {
            if (!isnan(*(p2->factors + ocpt)))
                *(pr->factors + ocpt) += *(p2->factors + ocpt);
        }
    else
        for (ocpt = 0; ocpt < (ho + 1); ocpt++)
            if (!isnan(*(p1->factors + ocpt)))
                *(pr->factors + ocpt) += *(p1->factors + ocpt);
    return ho;
}

polynomial_order_t polynomial_sub(polynomial_t *p1, polynomial_t *p2, polynomial_t *pr)
{
    polynomial_order_t ocpt;
    for (ocpt = 0; ocpt <= p2->order; ocpt++)
        *(p2->factors + ocpt) *= -1.0f;
    return polynomial_add(p1, p2, pr);
}

void polynomial_calc_gmp_int(mpz_t acc, polynomial_item_t x, polynomial_t *p, mp_bitcnt_t precision)
{
    mpz_t fact, powd, term, xz, nmul;
    mpz_init2(fact, precision);
    mpz_init2(term, precision);
    mpz_init2(powd, precision);
    mpz_init2(xz, precision);
    mpz_init2(nmul, precision);
    mpz_set_d(nmul, -1.0f);
    polynomial_order_t ocpt;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        if (polynomial_getratio(ocpt, p).num != 0)
        {
            const polynomial_ratio_t ratio = polynomial_getratio(ocpt, p);
            mpz_set_d(fact, (float)ratio.num);
            mpz_set_d(xz, (float)x);
            const unsigned long xo = ocpt;
            mpz_pow_ui(powd, xz, xo);
            mpz_mul(term, fact, powd);
            mpz_div_ui(term, term, (unsigned long)ratio.denom);
            if (ratio.num < 0)
                mpz_mul(term, term, nmul);
            mpz_add(acc, acc, term);
        }
    mpz_clear(nmul);
    mpz_clear(fact);
    mpz_clear(powd);
    mpz_clear(term);
    mpz_clear(xz);
}

void polynomial_calc_gmp_mpfr(mpfr_t acc, polynomial_item_t x, polynomial_t *p, mpfr_prec_t precision)
{
    const short debug = 0;
    mpfr_t denom, fact, powd, term, xz;
    polynomial_order_t ocpt;

    mpfr_init2(denom, precision);
    mpfr_init2(fact, precision);
    mpfr_init2(term, precision);
    mpfr_init2(powd, precision);
    mpfr_init2(xz, precision);

    mpfr_set_d(acc, 0.0f, MPFR_RNDN);
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        if (polynomial_getratio(ocpt, p).num != 0)
        {
            const polynomial_ratio_t ratio = polynomial_getratio(ocpt, p);
            mpfr_set_d(denom, (double)ratio.denom, MPFR_RNDN);
            mpfr_set_d(fact, (double)ratio.num, MPFR_RNDN);
            mpfr_div(fact, fact, denom, MPFR_RNDN);
            mpfr_set_ld(xz, x, MPFR_RNDN);
            const unsigned long xo = ocpt;
            mpfr_pow_ui(powd, xz, xo, MPFR_RNDN);
            mpfr_mul(term, fact, powd, MPFR_RNDU);
            mpfr_add(acc, acc, term, MPFR_RNDN);
            if (debug && p->order > 512)
                mpfr_printf(
                    "\n-------------\n"
                    "fact\t%Rf\n"
                    "xz\t%Rf\n"
                    "powd\t%Rf\n"
                    "term\t%Rf\n"
                    "acc\t%Rf\n",
                    fact,
                    xz,
                    powd,
                    term,
                    acc);
        }
    mpfr_clear(denom);
    mpfr_clear(fact);
    mpfr_clear(term);
    mpfr_clear(powd);
    mpfr_clear(xz);
    mpfr_free_cache();
}