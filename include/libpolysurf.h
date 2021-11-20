/**
 * @file libpolysurf.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief lib polysurf entry points
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_LIBPOLSURF_
#define _SURFACES_LIBPOLSURF_

#include "integral.h"
#include "intersect.h"

/**
 * @brief polynomial derivate
 * 
 * @param p polynomial
 * @param d polynomial derivated
 */
extern void polysurf_derivate(polynomial_t *p, polynomial_t *d);

/**
 * @brief polynomial antiderivate
 * 
 * @param p polynomial
 * @param a polynomial antiderivated
 */
extern void polysurf_antiderivate(polynomial_t *p, polynomial_t *a);

/**
 * @brief polynomial signs study
 * 
 * @param p polynomial
 * @param signs 
 */
extern void polysurf_signs(polynomial_t *p, signs_t *signs);

/**
 * @brief polynomial roots finder
 * 
 * @param p polynomial
 * @param il interval 
 * @param roots 
 * @return polynomial_order_t 
 */
extern polynomial_order_t polysurf_roots(
    polynomial_t *p,
    interval_t il,
    polynomial_item_t *roots);

/**
 * @brief polynomial intersection points
 * 
 * @param p1 
 * @param p2 
 * @param ivl 
 * @param coords 
 * @return polynomial_order_t 
 */
extern polynomial_order_t polysurf_intersect(
    polynomial_t *p1,
    polynomial_t *p2,
    interval_t ivl,
    coord_t *coords);

/**
 * @brief polynomial integral
 * 
 * @param p polynomial
 * @param il interval
 * @param result as char*
 * @param ext mp params
 */
extern void polysurf_integral(
    polynomial_t *p,
    interval_t il,
    char *result,
    factory_ext_t ext);

#endif // _SURFACES_LIBPOLSURF_