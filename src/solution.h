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
#include "profile.h"
#include "integral.h"

#define SYM_ITGR "∫"
#define ITGR_UA "u.a"
#define SOL_FN "f(x)"
#define SOL_ITGFN "F(x)"
#define SOL_EQ_FMT "%s = %.8f*x+%.8f\n"
#define SOL_ITGR_LIM "%s [%s .. %s]\n"
#define SOL_RES "%s%sdx = %s %s\n"
#define SOL_FMT_BUFF_LEN 12
#define SOL_NULL_CHAR '\0'
#define SOL_DOT_CHAR '.'
#define SOL_DOUBLE_FMT "%0.12f"
#define SOL_ELAPSE_FMT "\tElapse : %f s\n"

void solution_format_double(char *s, unsigned n);
void solution_equation(FILE *streamout, polynomial_t *p);
void solution_print(FILE *streamout, polynomial_t *p, interval_t li, polynomial_item_t sol, char *title, profile_t *prof);

#endif // _SURFACES_SOL_