
#include "roots.h"
#include "derivative.h"
#include "mpfr.h"

/**
 * @brief linear solver y = ax + b = 0
 * 
 * @param p 
 * @param roots 
 * @return polynomial_order_t 
 */
static polynomial_order_t roots_o1(polynomial_t *p, polynomial_item_t *roots)
{
    if (*(p->factors + 1) != 0 && *(p->factors + 0) != 0)
    {
        const polynomial_item_t a = *(p->factors + 1),
                                b = *(p->factors + 0);
        *(roots + 0) = -b / a;
        return 1;
    }
    else
    {
        *(roots + 0) = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief quadratic solver y = ax^2 + bx + c = 0
 * 
 * @param p 
 * @param roots 
 * @return polynomial_order_t 
 */
static polynomial_order_t roots_o2(polynomial_t *p, polynomial_item_t *roots)
{
    polynomial_item_t a = *(p->factors + p->order);
    if (a != 0)
    {
        const polynomial_item_t b = *(p->factors + 1),
                                c = *(p->factors + 0),
                                disc = (b * b) - 4 * (a * c);
        if (disc == 0)
        {
            *(roots + 0) = -b / (2 * a);
            return 1;
        }
        else if (disc > 0)
        {
            *(roots + 0) = (-b - sqrtl(disc)) / (2 * a);
            *(roots + 1) = (-b + sqrtl(disc)) / (2 * a);
            return 2;
        }
        else
            return 0;
    }
    else
        return 0;
}

/**
 * @brief newton raphson method
 * 
 * @param xinit 
 * @param nbit 
 * @param precision 
 * @param p polynomial
 * @param d derivated polynomial
 * @return polynomial_item_t 
 */
static polynomial_item_t newton_raphson(
    polynomial_item_t xinit,
    unsigned int nbit,
    polynomial_item_t precision,
    polynomial_t *p,
    polynomial_t *d)
{
    unsigned int i;
    polynomial_item_t x, y;
    for (x = xinit, y = 1, i = 0; i < nbit; x = y, i++)
    {
        y = x - polynomial_calc(x, p) / polynomial_calc(x, d);
        if (fabsl(x - y) < precision)
            return y;
    }
    return -INFINITY;
}

/**
 * @brief n order solver
 * 
 * @param p 
 * @param roots 
 * @param signs 
 * @return polynomial_order_t 
 */
static polynomial_order_t roots_on(
    polynomial_t *p,
    polynomial_item_t *roots,
    signs_t *signs)
{
    poly_signs_scan(p, signs);
    polynomial_t *d;
    d = (polynomial_t *)malloc(sizeof(polynomial_t));
    derivative_derivate(p, d);
    unsigned int i, cptr = 0;
    for (i = 0; i < signs->cpt; i++)
    {
        const coord_t c = *(signs->coords + i);
        const polynomial_item_t aroot = newton_raphson(
            c.x,
            ROOTS_NR_NBIT,
            ROOTS_NR_PRECISON,
            p,
            d);
        if (aroot != -INFINITY)
            *(roots + cptr++) = aroot;
    }
    polynomial_destruct(d);
    free(d);
    return cptr;
}

/**
 * @brief rootsfinder factory
 * 
 * @param p 
 * @param roots 
 * @return polynomial_order_t 
 */
polynomial_order_t roots_factory(
    polynomial_t *p,
    polynomial_item_t *roots)
{
    roots_reset(p, roots);
    if (p->order == 0)
        return 0;
    if (p->order == 1)
        return roots_o1(p, roots);
    if (p->order == 2)
        return roots_o2(p, roots);
    if (p->order > 2)
    {
        signs_t *signs;
        signs = malloc(sizeof(signs_t));
        signs->cpt = 0;
        signs->coords = malloc(sizeof(coord_t) * (p->order + 1));
        signs->interval = (interval_t){
            .l = ROOTS_SIGNS_INTERVAL_L,
            .h = ROOTS_SIGNS_INTERVAL_H};
        signs->step = ROOTS_SIGNS_STEP;
        polynomial_order_t nbroots = roots_on(p, roots, signs);
        free(signs->coords);
        free(signs);
        return nbroots;
    }
    return 0;
}

/**
 * @brief rootsfinder reset
 * 
 * @param p 
 * @param roots 
 */
void roots_reset(polynomial_t *p, polynomial_item_t *roots)
{
    polynomial_order_t cpto;
    for (cpto = 0; cpto < p->order; cpto++)
        *(roots + cpto) = 0.0f;
}
