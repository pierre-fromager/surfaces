
#include "riemannsum.h"

polynomial_item_t riemann_sum_rect(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 0; i < n; i++)
        sum += polynomial_calc(il.l + i * dx, p) * dx;
    return sum;
}

polynomial_item_t riemann_sum_trap(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n)
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

polynomial_item_t riemann_sum_mp(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 0; i < n; i++)
    {
        polynomial_item_t term = ((i * dx) + ((i + 1) * dx)) / 2.0f;
        sum += polynomial_calc(term, p);
    }
    return dx * sum;
}

polynomial_item_t riemann_sum_left(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 0; i < n; i++)
        sum += polynomial_calc(i * dx, p);
    return dx * sum;
}

polynomial_item_t riemann_sum_right(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n)
{
    polynomial_item_t i, sum = 0;
    const polynomial_item_t dx = (il.h - il.l) / n;
    for (i = 1; i < n + 1; i++)
        sum += polynomial_calc(i * dx, p);
    return dx * sum;
}
