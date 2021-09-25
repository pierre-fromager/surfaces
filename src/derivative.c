
#include "derivative.h"

void derivative_derivate(polynomial_t *psrc, polynomial_t *pdst)
{
    polynomial_order_t cpto;
    const polynomial_order_t pdst_order = (psrc->order > 0) ? psrc->order - 1 : 0;    
    polynomial_construct(pdst_order, pdst);
    for (cpto = psrc->order + 1; cpto > 0; cpto--)
    {
        const polynomial_item_t actfac = polynomial_getfactor(cpto, psrc);
        if (actfac != 0)
        {
            //const polynomial_item_t actorder = polynomial_getorder(cpto, psrc);
            polynomial_setfactor(cpto - 1, actfac * cpto, pdst);
            //*(pdst->factors + cpto - 1) = *(pdst->orders + cpto);
        }
    }
}