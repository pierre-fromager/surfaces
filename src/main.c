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

#define TITLE_SOL_SITZM "Integrate trapezoid method"
#define TITLE_SOL_SIMPM "Integrate middle point method"
#define TITLE_SOL_MPTM "Integrate intervals I%u"
#define FN0_S 0.5f
#define FN0_O 3.0f
#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP
#define __ACCURA 16.0f
#define __ACBASE 10.0f

arguments_t args;
static interval_t single_interval(void);

static interval_t single_interval()
{
    return (interval_t){.l = IL_L, .h = IL_H};
}

static void set_intervals(intervals_t itvls, interval_t itvl_tpl)
{
    itvls[0] = itvls[1] = itvl_tpl;
    itvls[0].h = itvls[1].l = (itvls[0].l + itvls[0].h) / 2;
}

static double trapz_s_interval(polynomial_t *p, interval_t itvl)
{
    return integral_poly_trapez(p, itvl);
}

static double trapz_m_intervals(polynomial_t *p, intervals_t itvls, unsigned nbintvls)
{
    unsigned itvlcpt;
    double sol, solsum = 0;
    char title[50];
    for (itvlcpt = 0; itvlcpt < nbintvls; itvlcpt++)
    {
        sol = integral_poly_trapez(p, itvls[itvlcpt]);
        solsum += sol;
        snprintf(title, sizeof(title), TITLE_SOL_MPTM, itvlcpt);
        solution_print(stdout, p, itvls[itvlcpt], sol, title);
    }
    return solsum;
}

int main(int argc, char *argv[])
{
    arguments_process(argc, argv, &args);

    polynomial_t *p;
    p = malloc(sizeof(polynomial_t));
    // y = 1/2x + 3
    polynomial_construct(1, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);

    const interval_t itvl_tpl = single_interval();
    const polynomial_item_t sol_s = trapz_s_interval(p, itvl_tpl);
    solution_print(stdout, p, itvl_tpl, sol_s, TITLE_SOL_SITZM);

    const polynomial_item_t sol_sf = integral_poly_midpnt(p, itvl_tpl);
    solution_print(stdout, p, itvl_tpl, sol_sf, TITLE_SOL_SIMPM);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    set_intervals(itvls, itvl_tpl);
    const polynomial_item_t sol_m = trapz_m_intervals(p, itvls, nbitvls);
    solution_print(stdout, p, itvl_tpl, sol_m, "Sum intervals I0-1");
    free(itvls);

    printf("Integrate with factory\n");
    printf("\t%sab  a:%0.1f b:%0.1f\n", SYM_ITGR, itvl_tpl.l, itvl_tpl.h);
    const polynomial_item_t partition_amount = pow(4.0f, 10.0f);
    const polynomial_item_t itgf_fact_sol = integral_factory(p, itvl_tpl);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgf_fact_sol);
    printf("\t%s : %0.12f\n", INTEG_EPSILON, sol_sf - itgf_fact_sol);

    // y = x^3 + 1/2x + 3
    polynomial_construct(4, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);
    polynomial_setfactor(3, 1.0f, p);
    const polynomial_item_t itgr_fact_sol = integral_poly_riemann(
        p,
        itvl_tpl,
        partition_amount);
    printf("\nRiemann iterative method ε ref\n");
    solution_equation(stdout, p);
    printf("\tPartition amount : %10.0f\n", partition_amount);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgr_fact_sol);

    const polynomial_item_t itgs_fact_sol = integral_poly_simpson(p, itvl_tpl);
    printf("\nSimpson method\n");
    solution_equation(stdout, p);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgs_fact_sol);
    printf("\t%s = %0.12f\n", INTEG_EPSILON, itgr_fact_sol - itgs_fact_sol);

    const polynomial_item_t itgn12_fact_sol = integral_poly_newton_cote_1_2(p, itvl_tpl);
    printf("\nNewton-cote-1-2 method\n");
    solution_equation(stdout, p);
    printf("\t%sf(x)dx = %0.12f\n", SYM_ITGR, itgn12_fact_sol);
    printf("\t%s = %0.12f\n", INTEG_EPSILON, itgr_fact_sol - itgn12_fact_sol);

    polynomial_destruct(p);

    return EXIT_SUCCESS;
}
