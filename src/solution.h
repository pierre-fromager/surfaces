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
#include "roots.h"

#define SYM_ITGR "∫"
#define ITGR_UA "u.a"
#define SOL_FN "f(x)"
#define SOL_EQ_FMT "%s = %.8f*x+%.8f\n"
#define SOL_ITGR_LIM "[%s..%s]"
#define SOL_RES "\t%s%sdx%s\n\t%s\n"
#define SOL_FMT_BUFF_LEN 1024 * 8
#define SOL_NULL_CHAR '\0'
#define SOL_DOT_CHAR '.'
#define SOL_DOUBLE_FMT_DISPLAY_LEN 5
#define SOL_DOUBLE_FMT "%Lf"
#define SOL_ELAPSE_FMT "\tElapse %fs\n"
#define SOL_TAB "\t"
#define SOL_LF "\n"

void solution_format_double(char *s, unsigned n);
void solution_equation(FILE *streamout, polynomial_t *p);
void solution_print(
    FILE *streamout,
    polynomial_t *p,
    interval_t li,
    char *result,
    char *title,
    profile_t *prof,
    unsigned int precision);

#endif // _SURFACES_SOL_