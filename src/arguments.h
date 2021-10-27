/**
 * @file arguments.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Polyreg arguments manager
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_ARGUMENTS_
#define _POLYREG_ARGUMENTS_

#include <stdlib.h>
#include <stdio.h>
#include <argp.h>
#include "polynomial_types.h"

#define PORE_NAME "surfaces"
#define PORE_VERSION "2.0"
#define PORE_MAINT_EMAIL "info@pier-infor.fr"
#define PORE_ARGS_DOC_ARG "equation"
#define PORE_ARGS_DOC "Polynomial surface " PORE_VERSION

typedef struct arguments_s
{
    char *args[1];
    int debug;
    int verbose;
    unsigned int precision;
    polynomial_item_t low;
    polynomial_item_t high;
} arguments_t;

void arguments_process(int argc, char **argv, arguments_t *arguments);

#endif // _POLYREG_ARGUMENTS_