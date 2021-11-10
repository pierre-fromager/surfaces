/**
 * @file roots.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial roots finder factory
 * @version 0.1
 * @date 2021-31-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_ROOTS_
#define _SURFACES_ROOTS_

#define ROOTS_O3_MSG_DBG_0 "3 distinct real roots.\n"
#define ROOTS_O3_MSG_DBG_1 "repeated root and all its roots are real.\n"
#define ROOTS_O3_MSG_DBG_2 "1 real root and 2 non-real complex conjugate roots.\n"
#define ROOTS_NR_PRECISON 1e-16
#define ROOTS_NR_NBIT 10
#define ROOTS_SIGNS_STEP 0.1
#define ROOTS_SIGNS_INTERVAL_L -50.0f
#define ROOTS_SIGNS_INTERVAL_H 50.0f

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "signs.h"
#include "polynomial.h"

typedef struct root_complex_s
{
    polynomial_item_t real, imag;
} root_complex_t;

/**
 * @brief polynomial roots finder factory
 * 
 * @param p 
 * @param roots 
 * @return polynomial_order_t 
 */
polynomial_order_t roots_factory(polynomial_t *p, polynomial_item_t *roots);

/**
 * @brief reset polynomial roots
 * 
 * @param p 
 * @param roots 
 */
void roots_reset(polynomial_t *p, polynomial_item_t *roots);

#endif // _SURFACES_ROOTS_