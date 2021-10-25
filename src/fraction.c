
#include "fraction.h"

static int fraction_gcd(int a, int b)
{
    if (a == 0)
        return b;
    return fraction_gcd(b % a, a);
}

static void fraction_reduce(polynomial_ratio_t *r)
{
    int cf;
    cf = fraction_gcd(r->num, r->denom);
    r->denom = r->denom / cf;
    r->num = r->num / cf;
    if (r->denom < 0) {
        r->denom *= -1;
        r->num *= -1;
    }
}

polynomial_ratio_t fraction_add(polynomial_ratio_t ra, polynomial_ratio_t rb)
{
    polynomial_ratio_t r;
    r.denom = fraction_gcd(ra.denom, rb.denom);
    r.denom = (ra.denom * rb.denom) / r.denom;
    r.num = (ra.num * (r.denom / ra.denom)) + (rb.num * (r.denom / rb.denom));
    fraction_reduce(&r);
    return r;
}
