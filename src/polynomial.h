
#ifndef _SURFACES_POLYNOMIAL_
#define _SURFACES_POLYNOMIAL_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "polynomial_types.h"

void polynomial_construct(polynomial_order_t o, polynomial_t *p);
void polynomial_destruct(polynomial_t *p);
void polynomial_setfactor(polynomial_order_t o, polynomial_item_t v, polynomial_t *p);
polynomial_item_t polynomial_getfactor(polynomial_order_t o, polynomial_t *p);
polynomial_item_t polynomial_getorder(polynomial_order_t o, polynomial_t *p);
polynomial_item_t polynomial_calc(polynomial_item_t x, polynomial_t *p);

#endif // _SURFACES_POLYNOMIAL_