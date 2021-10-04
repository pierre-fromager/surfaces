
#include "polynomial.h"

void polynomial_construct(polynomial_order_t o, polynomial_t *p)
{
    polynomial_order_t ocpt;
    const size_t asize = sizeof(polynomial_item_t) * (o + 1);
    const polynomial_item_t ifactor = 0;
    p->order = o;
    p->orders = malloc(asize);
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        *(p->orders + ocpt) = ocpt;
    p->factors = malloc(asize);
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        *(p->factors + ocpt) = ifactor;
}

void polynomial_setfactor(polynomial_order_t o, polynomial_item_t v, polynomial_t *p)
{
    *(p->factors + o) = v;
}

polynomial_item_t polynomial_getfactor(polynomial_order_t o, polynomial_t *p)
{
    return isnan(*(p->factors + o)) ? 0 : *(p->factors + o);
}

polynomial_item_t polynomial_getorder(polynomial_order_t o, polynomial_t *p)
{
    return *(p->orders + o);
}

polynomial_item_t polynomial_calc(polynomial_item_t x, polynomial_t *p)
{
    polynomial_order_t ocpt;
    polynomial_item_t sum = 0;
    for (ocpt = 0; ocpt < p->order + 1; ocpt++)
        if (*(p->factors + ocpt) != 0.0f)
            sum += polynomial_getfactor(ocpt, p) * powl(x, polynomial_getorder(ocpt, p));
    return sum;
}

void polynomial_destruct(polynomial_t *p)
{
    free(p->factors);
    free(p->orders);
}