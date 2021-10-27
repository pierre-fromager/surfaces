/**
 * @file polynomial.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial management
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _SURFACES_POLYNOMIAL_
#define _SURFACES_POLYNOMIAL_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include <mpfr.h>
#include "polynomial_types.h"
#include "fraction.h"

/**
 * @brief mem alloc
 * 
 * @param o 
 * @param p 
 */
void polynomial_construct(polynomial_order_t o, polynomial_t *p);

/**
 * @brief reset polynomail values to default
 * 
 * @param p 
 */
void polynomial_reset(polynomial_t *p);

/**
 * @brief mem free
 * 
 * @param p 
 */
void polynomial_destruct(polynomial_t *p);

/**
 * @brief set polynomial factor
 * 
 * @param o 
 * @param v 
 * @param p 
 */
void polynomial_setfactor(polynomial_order_t o, polynomial_item_t v, polynomial_t *p);

/**
 * @brief set polynomial ratio
 * 
 * @param o 
 * @param num 
 * @param denom 
 * @param p 
 */
void polynomial_setratio(polynomial_order_t o, int num, int denom, polynomial_t *p);

/**
 * @brief add ratio to current ratio 
 * 
 * @param o 
 * @param r 
 * @param p 
 */
void polynomial_addratio(polynomial_order_t o, polynomial_ratio_t r, polynomial_t *p);

/**
 * @brief get polynomial factor
 * 
 * @param o 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_getfactor(polynomial_order_t o, polynomial_t *p);

/**
 * @brief get polynomial degree for a given order ;-)
 * 
 * @param o 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_getorder(polynomial_order_t o, polynomial_t *p);

/**
 * @brief get polynomial ratio for a given degree
 * 
 * @param o 
 * @param p 
 * @return polynomial_ratio_t 
 */
polynomial_ratio_t polynomial_getratio(polynomial_order_t o, polynomial_t *p);

/**
 * @brief fix for powl odd exp
 * 
 * @param f 
 * @param e 
 * @return polynomial_item_t 
 */
polynomial_item_t _powl(polynomial_item_t f, polynomial_item_t e);

/**
 * @brief calculate polynomial value for x
 * 
 * @param x 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_calc(polynomial_item_t x, polynomial_t *p);

/**
 * @brief calculate polynomial gmp(int) arbitray precision value for x
 * 
 * @param acc 
 * @param x 
 * @param p 
 * @param precision 
 */
void polynomial_calc_gmp_int(mpz_t acc, polynomial_item_t x, polynomial_t *p, mp_bitcnt_t precision);

#endif // _SURFACES_POLYNOMIAL_