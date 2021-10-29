/**
 * @file integral_types.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial types
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _SURFACES_INTEGRAL_TYPES_
#define _SURFACES_INTEGRAL_TYPES_

typedef enum
{
    riemann_trapezoid,
    riemann_middle_point,
    riemann_rectangle,
    riemann_left,
    riemann_right,
} integral_riemann_method_t;

typedef enum
{
    ee_mpz = 0,
    ee_mpfr = 1,
} integral_ap_engine_t;

typedef struct factory_ext_s
{
    integral_ap_engine_t eng;
    long precision;
} factory_ext_t;

#endif // _SURFACES_INTEGRAL_TYPES_