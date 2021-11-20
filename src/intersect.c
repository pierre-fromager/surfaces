
#include "intersect.h"

polynomial_order_t poly_intersect(
    polynomial_t *p1,
    polynomial_t *p2,
    interval_t ivl,
    coord_t *coords)
{
    polynomial_order_t ho, itc, nbr;
    polynomial_item_t *roots;
    polynomial_t *psub = (polynomial_t *)malloc(sizeof(polynomial_t));
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    if (p1->order == p2->order && p1->order == 1)
        if (*(p1->factors + 1) == *(p2->factors + 1))
            return 0;

    polynomial_construct(ho, psub);
    ho = polynomial_sub(p1, p2, psub);
    roots = (polynomial_item_t *)malloc(sizeof(polynomial_item_t) * (ho + 1));
    nbr = roots_factory(psub, ivl, roots);
    for (itc = 0; itc < nbr + 1; itc++)
    {
        *(coords + itc) = (coord_t){
            .x = *(roots + itc),
            .y = polynomial_calc(*(roots + itc), p1)};
    }
    free(roots);
    polynomial_destruct(psub);
    free(psub);
    return nbr;
}