/**
 * @file main.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief   surface calculus for order 1 fn
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "integral.h"
#include "solution.h"

int main(int argc, char *argv[])
{
    arguments_t args;
    arguments_process(argc, argv, &args);
    linear_fn_t fn0 = {
        .s = 0.5,
        .o = 3.0};
    integral_t ifn0 = {
        .l = 0.0,
        .h = 5.0};
    print_sol(stdout, fn0, ifn0, linsurf(fn0, ifn0));
    return EXIT_SUCCESS;
}
