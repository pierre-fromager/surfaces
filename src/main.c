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
#include "integral.h"
#include "solution.h"

#define TITLE_SOL_SITZM "Single interval ITG trapezoid method"
#define TITLE_SOL_SIMPM "Single interval ITG middle point method"
#define TITLE_SOL_MPTM "Multiple intervals ITG trapz method"
#define FN0_S 0.5f
#define FN0_O 3.0f
#define IVL_L 0.0f
#define IVL_STEP 1.0f
#define IVL_H 5.0f / IVL_STEP
#define __ACCURA 16.0f
#define __ACBASE 10.0f

arguments_t args;
static interval_t single_interval(void);

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
    return integral_trapez(f, itvl);
}

static double trapz_m_intervals(linear_fn_t f, intervals_t itvls, unsigned nbintvls)
{
    unsigned itvlcpt;
    double sol, solsum = 0;
    for (itvlcpt = 0; itvlcpt < nbintvls; itvlcpt++)
    {
        sol = integral_trapez(f, itvls[itvlcpt]);
        solsum += sol;
        print_sol(stdout, f, itvls[itvlcpt], sol, TITLE_SOL_MPTM);
    }
    return solsum;
}

int main(int argc, char *argv[])
{
    arguments_process(argc, argv, &args);

    linear_fn_t f = {.s = FN0_S, .o = FN0_O};
    const interval_t itvl_tpl = single_interval();
    const double sol_s = trapz_s_interval(f, itvl_tpl);
    print_sol(stdout, f, itvl_tpl, sol_s, TITLE_SOL_SITZM);

    const double sol_sf = integral_midpnt(f, itvl_tpl);
    print_sol(stdout, f, itvl_tpl, sol_sf, TITLE_SOL_SIMPM);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    set_intervals(itvls, itvl_tpl);
    const double sol_m = trapz_m_intervals(f, itvls, nbitvls);
    free(itvls);

    assert(around(sol_s, __ACCURA) == around(sol_sf, __ACCURA));
    assert(around(sol_s, __ACCURA) == around(sol_m, __ACCURA));

    polynomial_t *p;
    p = malloc(sizeof(polynomial_t));
    polynomial_construct(1, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);
    const polynomial_item_t partition_size = pow(4.0f, 10.0f);
    const polynomial_item_t itgf_fact_sol = integral_factory(
        p,
        itvl_tpl,
        partition_size);
    printf("Using integral factory with polynomial form same f(x) and interval\n");
    printf("\t%sab  a:%0.1f b:%0.1f\n", SYM_ITGR, itvl_tpl.l, itvl_tpl.h);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgf_fact_sol);
    printf("\t%s : %0.12f\n", INTEG_EPSILON, sol_sf - itgf_fact_sol);
    const polynomial_item_t itgr_fact_sol = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_size);
    printf("\nUsing riemann sum with polynomial form same f(x) and interval\n");
    printf("\tParition size : %10.0f\n", partition_size);
    printf("\t%sab  a:%0.1f b:%0.1f\n", SYM_ITGR, itvl_tpl.l, itvl_tpl.h);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgr_fact_sol);
    printf("\t%s : %0.12f\n", INTEG_EPSILON, sol_sf - itgr_fact_sol);

    polynomial_destruct(p);

    return EXIT_SUCCESS;
}
