/**
 * @file solution.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief surface solution manager
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_SOL_
#define _SURFACES_SOL_

#include <stdlib.h>
#include <stdio.h>
#include "integral.h"

#define SYM_ITGR "∫"
#define ITGR_UA "u.a"
#define LFN "f(x)"
#define ITGFN "F(x)"
#define SOL_EQ_FMT "%s = %.2f*x+%.2f\n"
#define SOL_ITGR_LIM "%slh => l:%.2f h:%.2f\n"
#define SOL_RES "%s = %s%sdx = %.3f %s\n"

void print_sol(FILE *streamout, linear_fn_t lf, integral_t li, double sol);

#endif // _SURFACES_SOL_