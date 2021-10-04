
#ifndef _SURFACES_INTERVAL_
#define _SURFACES_INTERVAL_

#include "polynomial.h"

typedef struct interval_s
{
    polynomial_item_t l, h;
} interval_t;

typedef interval_t *intervals_t;

#endif // _SURFACES_INTERVAL_