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
#define IVL_STEP 1.0f
#define IVL_H 5.0f / IVL_STEP
#define __ACCURA 16.0f
#define __ACBASE 10.0f

arguments_t args;

static double around(double n, double i);
static interval_t single_interval(void);
static void set_intervals(intervals_t itvls, interval_t itvl_tpl);
static double trapz_s_interval(linear_fn_t f, interval_t interval);
static double trapz_m_intervals(linear_fn_t f, intervals_t itvls, unsigned nbintvls);

static double around(double n, double i)
{
    return floor(pow(__ACBASE, i) * n) / pow(__ACBASE, i);
}

static interval_t single_interval()
{
    return (interval_t){.l = IVL_L, .h = IVL_H};
}

static void set_intervals(intervals_t itvls, interval_t itvl_tpl)
{
    itvls[0] = itvls[1] = itvl_tpl;
    itvls[0].h = itvls[1].l = (itvls[0].l + itvls[0].h) / 2;
}

static double trapz_s_interval(linear_fn_t f, interval_t itvl)
{
    return integ_trapez(f, itvl);
}

static double trapz_m_intervals(linear_fn_t f, intervals_t itvls, unsigned nbintvls)
{
    unsigned itvlcpt;
    double sol, solsum = 0;
    for (itvlcpt = 0; itvlcpt < nbintvls; itvlcpt++)
    {
        sol = integ_trapez(f, itvls[itvlcpt]);
        solsum += sol;
        printf("%s\n", "Multiple intervals integ trapz method");
        print_sol(stdout, f, itvls[itvlcpt], sol);
    }
    return solsum;
}

int main(int argc, char *argv[])
{
    arguments_process(argc, argv, &args);

    printf("%s\n", "Single interval integ trapz method");
    linear_fn_t f = {.s = FN0_S, .o = FN0_O};
    const interval_t itvl_tpl = single_interval();
    const double sol_s = trapz_s_interval(f, itvl_tpl);
    print_sol(stdout, f, itvl_tpl, sol_s);
    printf("%s\n", "Single interval integ middle point method");
    const double sol_sf = integ_midpnt(f, itvl_tpl);
    print_sol(stdout, f, itvl_tpl, sol_sf);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    set_intervals(itvls, itvl_tpl);
    const double sol_m = trapz_m_intervals(f, itvls, nbitvls);
    free(itvls);

    assert(around(sol_s, __ACCURA) == around(sol_m, __ACCURA));
    return EXIT_SUCCESS;
}
