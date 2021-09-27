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
#define SOL_FN "f(x)"
#define SOL_ITGFN "F(x)"
#define SOL_EQ_FMT "%s = %.8f*x+%.8f\n"
#define SOL_ITGR_LIM "%slh => l:%.8f h:%.8f\n"
#define SOL_RES "%s = %s%sdx = %.18f %s\n"

void solution_print(FILE *streamout, polynomial_t *p, interval_t li, polynomial_item_t sol, char *title);

#endif // _SURFACES_SOL_