/**
 * @file fraction.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief fractions
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_FRACTIONS_
#define _SURFACES_FRACTIONS_

#include <stdio.h>
#include "polynomial_types.h"

polynomial_ratio_t fraction_add(polynomial_ratio_t ra, polynomial_ratio_t rb);

#endif // _SURFACES_FRACTIONS_