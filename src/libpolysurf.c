
#include "libpolysurf.h"

extern void polysurf_derivate(polynomial_t *p, polynomial_t *d)
{
    derivative_derivate(p, d);
}

extern void polysurf_antiderivate(polynomial_t *p, polynomial_t *a)
{
    derivative_antiderivate(p, a);
}

extern void polysurf_signs(polynomial_t *p, signs_t *signs)
{
    poly_signs_scan(p, signs);
}

extern polynomial_order_t polysurf_roots(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t *roots)
{
    return roots_factory(p, il, roots);
}

extern void polysurf_integral(
    polynomial_t *p,
    interval_t il,
    char *result,
    factory_ext_t ext)
{
    integral_factory(p, il, result, ext);
}

extern polynomial_order_t polysurf_intersect(
    polynomial_t *p1,
    polynomial_t *p2,
    interval_t ivl,
    coord_t *coords)
{
    return poly_intersect(p1, p2, ivl, coords);
}
