/**
 * @file derivative.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial derivate and antiderivate
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_DERIVATIVE_
#define _SURFACES_DERIVATIVE_

#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

/**
 * @brief polynomial derivate
 * 
 * @param psrc 
 * @param pdst 
 */
void derivative_derivate(polynomial_t *psrc, polynomial_t *pdst);

/**
 * @brief polynomial antiderivate
 * 
 * @param psrc 
 * @param pdst 
 */
void derivative_antiderivate(polynomial_t *psrc, polynomial_t *pdst);

#endif // _SURFACES_DERIVATIVE_