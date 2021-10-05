
#ifndef _SURFACES_POLYNOMIAL_TYPES_
#define _SURFACES_POLYNOMIAL_TYPES_

typedef unsigned polynomial_order_t;
typedef long double polynomial_item_t;

typedef struct polynomial_s
{
    polynomial_order_t order;
    polynomial_item_t *orders;
    polynomial_item_t *factors;
} polynomial_t;

#endif // _SURFACES_POLYNOMIAL_TYPES_