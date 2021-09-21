
#ifndef _SURFACES_INTEG_
#define _SURFACES_INTEG_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct linear_fn_s
{
    double s, o;
} linear_fn_t;

typedef struct interval_s
{
    double l, h;
} interval_t;

typedef interval_t *intervals_t; 

double integ_trapezoid(linear_fn_t lf, interval_t li);

#endif // _SURFACES_INTEG_