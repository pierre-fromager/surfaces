

#ifndef _SURFACES_INTGR_
#define _SURFACES_INTGR_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct linear_fn_s
{
    double s, o;
} linear_fn_t;

typedef struct integral_s
{
    double l, h;
} integral_t;

double linsurf(linear_fn_t lf, integral_t li);

#endif // _SURFACES_INTGR_