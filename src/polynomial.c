
#include "polynomial.h"

static void polynomial_debug(polynomial_t *poly)
{
    unsigned ocpt;
    printf("\nfs : %zu os : %zu\n", sizeof(poly->factors), sizeof(poly->orders));
    for (ocpt = 0; ocpt < poly->order; ocpt++)
    {
        printf("factors[%u] : %0.10f\n", ocpt, *(poly->factors + ocpt));
        printf("orders[%u] : %0.10f\n", ocpt, *(poly->orders + ocpt));
    }
}

void polynomial_construct(unsigned order, polynomial_t *poly)
{
    unsigned ocpt;
    const size_t asize = sizeof(double) * order;
    const int factor = 0;
    poly->order = order;
    poly->orders = malloc(asize);
    for (ocpt = 0; ocpt < order; ocpt++)
        poly->orders[ocpt] = ocpt;
    poly->factors = malloc(asize);
    memset(poly->factors, factor, asize);
#ifdef POLYNOMIAL_DEBUG
    polynomial_debug(poly);
#endif
}

void polynomial_setfactor(
    polynomial_order_t order,
    polynomial_item_t value,
    polynomial_t *poly)
{
    *(poly->factors + order) = value;
}

double polynomial_calc(double x, polynomial_t *poly)
{
    unsigned ocpt;
    double sum = 0;
    for (ocpt = 0; ocpt < poly->order; ocpt++)
        sum += poly->factors[ocpt] * x * pow(10.0f, poly->orders[ocpt]);
    return sum;
}

void polynomial_destruct(polynomial_t *poly)
{
    free(poly->factors);
    free(poly->orders);
}