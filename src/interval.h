/**
 * @file interval.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief integral interval
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_INTERVAL_
#define _SURFACES_INTERVAL_

#include "polynomial_types.h"

typedef struct interval_s
{
    polynomial_item_t l, h;
} interval_t;

typedef interval_t *intervals_t;

#endif // _SURFACES_INTERVAL_