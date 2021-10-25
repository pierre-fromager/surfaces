/**
 * @file main.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief  surface calc for polynomial
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arguments.h"
#include "parser.h"
#include "integral.h"
#include "solution.h"
#include "profile.h"

#define STR_NL "%s\n"
#define TITLE_SOL_SITZM "Factory"
#define PARSER_ERR_MSG "Parser compilation failed."
#define POLY_MAX_ORDER 4096 * 1
#define DEFAULT_EQ "1/2x+3"

arguments_t args;

int main(int argc, char *argv[])
{
    arguments_process(argc, argv, &args);

    FILE *streamout = stdout;
    char *result;
    result = malloc(sizeof(char) * INTEG_FACTORY_BUF_SIZE);

    profile_t *prof;
    prof = (profile_t *)malloc(sizeof(profile_t));

    polynomial_t *p;
    p = (polynomial_t *)malloc(sizeof(polynomial_t));

    polynomial_construct(POLY_MAX_ORDER, p);
    int parser_err;
    parser_err = (args.args[0] != NULL)
                     ? parser_parse(args.args[0], p)
                     : parser_parse(DEFAULT_EQ, p);
    if (parser_err != 0)
        fprintf(streamout, STR_NL, PARSER_ERR_MSG);

    const interval_t interval = {
        .l = args.low,
        .h = args.high,
    };

    profile_start(prof);
    integral_factory(p, interval, result);
    profile_stop(prof);

    if (args.verbose == 0)
        fprintf(streamout, STR_NL, result);
    else
        solution_print(streamout, p, interval, result, TITLE_SOL_SITZM, prof);

    polynomial_destruct(p);
    free(result);
    free(p);
    free(prof);

    return EXIT_SUCCESS;
}
