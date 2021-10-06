/**
 * @file riemannsum.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial integration
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_RIESMANNSUM_
#define _SURFACES_RIESMANNSUM_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "polynomial.h"

typedef enum
{
    riemann_trapezoid,
    riemann_middle_point,
    riemann_rectangle,
    riemann_left,
    riemann_right,
} integral_riemann_method_t;

/**
 * @brief riemann sum rectangle method
 * 
 * @param p 
 * @param il 
 * @param n 
 * @return polynomial_item_t 
 */
polynomial_item_t riemann_sum_rect(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n);

/**
 * @brief riemann sum trapezoid method
 * 
 * @param p 
 * @param il 
 * @param n 
 * @return polynomial_item_t 
 */
polynomial_item_t riemann_sum_trap(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n);

/**
 * @brief riemann sum middle point method
 * 
 * @param p 
 * @param il 
 * @param n 
 * @return polynomial_item_t 
 */
polynomial_item_t riemann_sum_mp(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n);

/**
 * @brief riemann sum middle left method
 * 
 * @param p 
 * @param il 
 * @param n 
 * @return polynomial_item_t 
 */
polynomial_item_t riemann_sum_left(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n);

/**
 * @brief riemann sum middle right method
 * 
 * @param p 
 * @param il 
 * @param n 
 * @return polynomial_item_t 
 */
polynomial_item_t riemann_sum_right(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n);

#endif // _SURFACES_RIESMANNSUM_