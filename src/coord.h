/**
 * @file coord.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief 2d coordinates type
 * @version 0.1
 * @date 2021-10-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACE_COORD_
#define _SURFACE_COORD_

#include "polynomial_types.h"

typedef struct coord_s
{
    polynomial_item_t x;
    polynomial_item_t y;
} coord_t;

#endif // _SURFACE_COORD_