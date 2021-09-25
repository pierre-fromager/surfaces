
#include "derivative.h"

void derivative_derivate(polynomial_t *psrc, polynomial_t *pdst)
{
    polynomial_order_t cpto;
    polynomial_item_t actfac;
    const polynomial_order_t pdst_order = (psrc->order > 0) ? psrc->order - 1 : 0;
    polynomial_construct(pdst_order, pdst);
    for (cpto = psrc->order + 1; cpto > 0; cpto--)
    {
        actfac = polynomial_getfactor(cpto, psrc);
        if (actfac != 0)
            polynomial_setfactor(cpto - 1, actfac * cpto, pdst);
    }
}