/**
 * @file intersect.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial intersection
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_INTERSECT_
#define _SURFACES_INTERSECT_

#include "polynomial.h"
#include "interval.h"
#include "roots.h"
#include "coord.h"

polynomial_order_t poly_intersect(
    polynomial_t *p1,
    polynomial_t *p2,
    interval_t ivl,
    coord_t *coords);

#endif // _SURFACES_INTERSECT_