/**
 * @file integral.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial integration
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_INTEGRAL_
#define _SURFACES_INTEGRAL_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interval.h"
#include "polynomial.h"
#include "derivative.h"
#include "riemannsum.h"

#define INTEG_TWO 2.0f
#define INTEG_EPSILON "ε"
#define INTEG_FACTORY_BUF_SIZE 1024 * 10

typedef enum
{
    riemann_trapezoid,
    riemann_middle_point,
    riemann_rectangle,
    riemann_left,
    riemann_right,
} integral_riemann_method_t;

/**
 * @brief polynomial integration middle point
 * 
 * @param p 
 * @param il 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_poly_midpnt(polynomial_t *p, interval_t il);

/**
 * @brief polynomial integration trapezoid
 * 
 * @param p 
 * @param il 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_poly_trapez(polynomial_t *p, interval_t il);

/**
 * @brief polynomial integration simpson method
 * 
 * @param p 
 * @param il 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_poly_simpson(polynomial_t *p, interval_t il);

/**
 * @brief polynomial integration newton cote
 * 
 * @param p 
 * @param il 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_poly_newton_cote_1_2(polynomial_t *p, interval_t il);

/**
 * @brief polynomial integration antiderivatve method
 * 
 * @param p 
 * @param il 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_poly_reference(polynomial_t *p, interval_t il);

/**
 * @brief polynomial integration riemann factory
 * 
 * @param p 
 * @param il 
 * @param n 
 * @param m 
 * @return polynomial_item_t 
 */
polynomial_item_t integral_factory_riemann(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t n,
    integral_riemann_method_t m);

/**
 * @brief polynomial integration factory
 * 
 * @param p 
 * @param il 
 * @param result
 */
void integral_factory(polynomial_t *p, interval_t il, char *result, mp_bitcnt_t precision);

/**
 * @brief polynomial integration with gmp arbitrary precision
 * 
 * @param acc 
 * @param p 
 * @param il 
 * @param precision 
 */
void integral_poly_reference_gmp(mpz_t acc, polynomial_t *p, interval_t il, mp_bitcnt_t precision);

#endif // _SURFACES_INTEGRAL_