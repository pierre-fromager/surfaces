/**
 * @file polynomial_types.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial types
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _SURFACES_POLYNOMIAL_TYPES_
#define _SURFACES_POLYNOMIAL_TYPES_

typedef unsigned polynomial_order_t;
typedef long double polynomial_item_t;

typedef struct polynomial_ratio_s
{
    int num;
    int denom;
} polynomial_ratio_t;

typedef struct polynomial_s
{
    polynomial_order_t order;
    polynomial_order_t *orders;
    polynomial_item_t *factors;
    polynomial_ratio_t *fratios;
} polynomial_t;

#endif // _SURFACES_POLYNOMIAL_TYPES_