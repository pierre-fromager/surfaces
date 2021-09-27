
#ifndef _SURFACES_INTEGRAL_
#define _SURFACES_INTEGRAL_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "linearfn.h"
#include "polynomial.h"
#include "derivative.h"

#define INTEG_TWO 2.0f
#define INTEG_EPSILON "ε"

double integral_midpnt(linear_fn_t lf, interval_t li);
double integral_trapez(linear_fn_t lf, interval_t li);

polynomial_item_t integral_factory(polynomial_t *p, interval_t li, polynomial_item_t n);
polynomial_item_t integral_poly_midpnt(polynomial_t *p, interval_t li);
polynomial_item_t integral_poly_riemann(polynomial_t *p, interval_t li, polynomial_item_t n);
polynomial_item_t integral_poly_simpson(polynomial_t *p, interval_t li);
polynomial_item_t integral_poly_newton_cote_1_2(polynomial_t *p, interval_t li);
polynomial_item_t integral_poly_newton_cote_2_2(polynomial_t *p, interval_t li);

#endif // _SURFACES_INTEGRAL_