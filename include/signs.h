/**
 * @file signs.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial signs
 * @version 0.1
 * @date 2021-10-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYNOMIAL_SIGNS_
#define _POLYNOMIAL_SIGNS_
#define POLYNOMIAL_SIGNS_VERBOSE 0
#define POLYNOMIAL_SIGNS_MSG_VERB "Signs changed @(%Lf,%Lf)\n"

#include "interval.h"
#include "coord.h"
#include "polynomial.h"

typedef struct signs_s
{
    unsigned int cpt;
    coord_t *coords;
    interval_t interval;
    polynomial_item_t step;
} signs_t;

/**
 * @brief set signs collection
 * 
 * @param p 
 * @param signs 
 */
void poly_signs_scan(polynomial_t *p, signs_t *signs);

#endif // _POLYNOMIAL_SIGNS_