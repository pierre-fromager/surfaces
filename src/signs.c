
#include "signs.h"

void poly_signs_scan(polynomial_t *p, signs_t *signs)
{
    polynomial_item_t x, y;
    short unsigned signa, signb;
    signa = (polynomial_calc(signs->interval.l, p) > 0) ? 1 : 0;
    for (x = signs->interval.l; x < signs->interval.h; x += signs->step)
    {
        y = polynomial_calc(x, p);
        signb = (y > 0) ? 1 : 0;
        if (signb != signa)
        {
            *(signs->coords + signs->cpt) = (coord_t){.x = x, .y = y};
            signs->cpt++;
            if (POLYNOMIAL_SIGNS_VERBOSE == 1)
                printf(POLYNOMIAL_SIGNS_MSG_VERB, x, y);
        }
        signa = signb;
    }
}