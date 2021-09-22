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
#include "integ.h"

#define SYM_ITGR "∫"
#define ITGR_UA "u.a"
#define LFN "f(x)"
#define ITGFN "F(x)"
#define SOL_EQ_FMT "%s = %.8f*x+%.8f\n"
#define SOL_ITGR_LIM "%slh => l:%.8f h:%.8f\n"
#define SOL_RES "%s = %s%sdx = %.18f %s\n"

void print_sol(FILE *streamout, linear_fn_t lf, interval_t li, double sol);

#endif // _SURFACES_SOL_