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
#include "polynomial_types.h"

/**
 * @brief mem alloc
 * 
 * @param o 
 * @param p 
 */
void polynomial_construct(polynomial_order_t o, polynomial_t *p);

/**
 * @brief mem free
 * 
 * @param p 
 */
void polynomial_destruct(polynomial_t *p);

/**
 * @brief set polynome factor
 * 
 * @param o 
 * @param v 
 * @param p 
 */
void polynomial_setfactor(polynomial_order_t o, polynomial_item_t v, polynomial_t *p);

/**
 * @brief get polynome factor
 * 
 * @param o 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_getfactor(polynomial_order_t o, polynomial_t *p);

/**
 * @brief get polynome higher degree
 * 
 * @param o 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_getorder(polynomial_order_t o, polynomial_t *p);

/**
 * @brief calculate polynome value for x
 * 
 * @param x 
 * @param p 
 * @return polynomial_item_t 
 */
polynomial_item_t polynomial_calc(polynomial_item_t x, polynomial_t *p);

#endif // _SURFACES_POLYNOMIAL_