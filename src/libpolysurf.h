/**
 * @file libpolysurf.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief lib polynomial surface
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_LIBPOLSURF_
#define _SURFACES_LIBPOLSURF_

#include "integral.h"

extern void polysurf_factory(
    polynomial_t *p, 
    interval_t il, 
    char *result, 
    factory_ext_t ext);

#endif // _SURFACES_LIBPOLSURF_