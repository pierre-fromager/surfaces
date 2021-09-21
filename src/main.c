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
#include <assert.h>
#include "arguments.h"
#include "integ.h"
#include "solution.h"

#define FN0_S 0.5f
#define FN0_O 3.0f
#define IVL_L 0.0f
#define IVL_M 2.0f
#define IVL_H 5.0f

static void demo_trapezoid(void);

static void demo_trapezoid()
{
    linear_fn_t f0 = {.s = FN0_S, .o = FN0_O};
    interval_t interval = {.l = IVL_L, .h = IVL_H};
    const double sol_ivl = integ_trapezoid(f0, interval);
    print_sol(stdout, f0, interval, sol_ivl);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    itvls[0] = interval;
    itvls[0].h = IVL_M;
    itvls[1] = interval;
    itvls[1].l =itvls[0].h;
    double sol_itvls0 = integ_trapezoid(f0, itvls[0]);
    print_sol(stdout, f0, itvls[0], sol_itvls0);
    double sol_itvls1 = integ_trapezoid(f0, itvls[1]);
    print_sol(stdout, f0, itvls[1], sol_itvls1);

    print_sol(stdout, f0, interval, sol_itvls0 + sol_itvls1);
    free(itvls);

    assert(sol_ivl == (sol_itvls0 + sol_itvls1));
}

int main(int argc, char *argv[])
{
    arguments_t args;
    arguments_process(argc, argv, &args);
    demo_trapezoid();
    return EXIT_SUCCESS;
}
