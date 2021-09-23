
#ifndef _SURFACES_INTEG_
#define _SURFACES_INTEG_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "linearfn.h"

#define INTEG_TWO 2.0f

double integ_midpnt(linear_fn_t lf, interval_t li);
double integ_trapez(linear_fn_t lf, interval_t li);

#endif // _SURFACES_INTEG_