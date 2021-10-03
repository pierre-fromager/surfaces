
#include "derivative.h"

void derivative_derivate(polynomial_t *psrc, polynomial_t *pdst)
{
    polynomial_order_t cpto;
    polynomial_item_t actfac;
    const polynomial_order_t pdst_order = (psrc->order > 0) ? psrc->order - 1 : 0;
    polynomial_construct(pdst_order, pdst);
    polynomial_setfactor(0, 0.0f, pdst);
    for (cpto = psrc->order + 1; cpto > 0; cpto--)
    {
        actfac = polynomial_getfactor(cpto, psrc);
        if (actfac != 0)
            polynomial_setfactor(cpto - 1, actfac * cpto, pdst);
    }
}

void derivative_antiderivate(polynomial_t *psrc, polynomial_t *pdst)
{
    polynomial_order_t cpto;
    polynomial_item_t actfac;
    const polynomial_order_t pdst_order = (psrc->order > 0) ? psrc->order + 1 : 0;
    polynomial_construct(pdst_order, pdst);
    polynomial_setfactor(0, 0.0f, pdst);
    for (cpto = 0; cpto < pdst_order + 1; cpto++)
    {
        actfac = polynomial_getfactor(cpto, psrc);
        if (actfac != 0.0f)
        {
            const polynomial_item_t nf = actfac / ((polynomial_item_t)cpto + 1.0f);
            polynomial_setfactor(cpto + 1, (isinf(nf)) ? 1.0f : nf, pdst);
        }
    }
}