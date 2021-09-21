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

arguments_t args;

static interval_t single_interval(void);
static void setup_itvls(intervals_t itvls, interval_t itvl_tpl);
static double trapezoid_s_interval(linear_fn_t f, interval_t interval);
static double trapezoid_m_intervals(linear_fn_t f, intervals_t itvls, unsigned nbintvls);

static interval_t single_interval()
{
    return (interval_t){.l = IVL_L, .h = IVL_H};
}

static void setup_itvls(intervals_t itvls, interval_t itvl_tpl)
{
    itvls[0] = itvls[1] = itvl_tpl;
    itvls[0].h = itvls[1].l = IVL_M;
}

static double trapezoid_s_interval(linear_fn_t f, interval_t itvl)
{
    return integ_trapezoid(f, itvl);
}

static double trapezoid_m_intervals(linear_fn_t f, intervals_t itvls, unsigned nbintvls)
{
    unsigned itvlcpt;
    double sol, solsum = 0;
    for (itvlcpt = 0; itvlcpt < nbintvls; itvlcpt++)
    {
        sol = integ_trapezoid(f, itvls[itvlcpt]);
        solsum += sol;
        print_sol(stdout, f, itvls[itvlcpt], sol);
    }
    return solsum;
}

int main(int argc, char *argv[])
{
    arguments_process(argc, argv, &args);

    linear_fn_t f = {.s = FN0_S, .o = FN0_O};
    const interval_t itvl_tpl = single_interval();
    const double sol_s = trapezoid_s_interval(f, itvl_tpl);
    print_sol(stdout, f, itvl_tpl, sol_s);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    setup_itvls(itvls, itvl_tpl);
    const double sol_m = trapezoid_m_intervals(f, itvls, nbitvls);
    free(itvls);
    
    assert(sol_s == sol_m);
    return EXIT_SUCCESS;
}
