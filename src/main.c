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

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "arguments.h"
#include "integral.h"
#include "solution.h"
#include "profile.h"

#define TITLE_SOL_SITZM "Integrate trapezoid method"
#define TITLE_SOL_SIMPM "Integrate middle point method"
#define TITLE_SOL_MPTM "Integrate intervals I%u"
#define TITLE_SOL_IL "Sum intervals [I0..I1]"
#define TITLE_SOL_FACTORY "Integrate with factory"
#define TITLE_SOL_RIEMANN "Riemann iterative method ε ref"
#define TITLE_SOL_SIMPSON "Simpson method"
#define TITLE_SOL_NC12 "Newton-cote-1-2 method"
#define EPSILON_FMT "\t%s %0.12f\n"
#define FN0_S 0.5f
#define FN0_O 3.0f
#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP
#define __ACCURA 16.0f
#define __ACBASE 10.0f

arguments_t args;

static interval_t interval_template(void);

static interval_t interval_template()
{
    return (interval_t){.l = IL_L, .h = IL_H};
}

static void set_intervals(intervals_t itvls, interval_t itvl_tpl)
{
    itvls[0] = itvls[1] = itvl_tpl;
    itvls[0].h = itvls[1].l = (itvls[0].l + itvls[0].h) / 2;
}

static double trapz_m_intervals(
    polynomial_t *p,
    intervals_t itvls,
    unsigned nbintvls,
    profile_t *prof)
{
    unsigned itvlcpt;
    polynomial_item_t sol, solsum = 0;
    char title[50];
    for (itvlcpt = 0; itvlcpt < nbintvls; itvlcpt++)
    {
        profile_start(prof);
        sol = integral_poly_trapez(p, itvls[itvlcpt]);
        profile_stop(prof);
        solsum += sol;
        snprintf(title, sizeof(title), TITLE_SOL_MPTM, itvlcpt);
        solution_print(stdout, p, itvls[itvlcpt], sol, title, prof);
    }
    return solsum;
}

int main(int argc, char *argv[])
{
    FILE *streamout = stdout;

    arguments_process(argc, argv, &args);

    profile_t *prof;
    prof = malloc(sizeof(profile_t));

    polynomial_t *p;
    p = malloc(sizeof(polynomial_t));

    // y = 1/2x + 3
    polynomial_construct(1, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);

    const interval_t itvl_tpl = interval_template();
    profile_start(prof);
    const polynomial_item_t sol_s = integral_poly_trapez(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, sol_s, TITLE_SOL_SITZM, prof);

    profile_start(prof);
    const polynomial_item_t sol_sf = integral_poly_midpnt(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, sol_sf, TITLE_SOL_SIMPM, prof);

    const unsigned nbitvls = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbitvls);
    set_intervals(itvls, itvl_tpl);
    const polynomial_item_t sol_m = trapz_m_intervals(p, itvls, nbitvls, prof);
    solution_print(streamout, p, itvl_tpl, sol_m, TITLE_SOL_IL, prof);
    free(itvls);

    profile_start(prof);
    const polynomial_item_t fact_sol = integral_factory(p, itvl_tpl);
    profile_stop(prof);
    solution_print(stdout, p, itvl_tpl, fact_sol, TITLE_SOL_FACTORY, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, sol_sf - fact_sol);

    // y = x^3 + 1/2x + 3
    polynomial_construct(4, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);
    polynomial_setfactor(3, 1.0f, p);

    const polynomial_item_t partition_amount = pow(4.0f, 10.0f);
    profile_start(prof);
    const polynomial_item_t itg_riemann = integral_poly_riemann(
        p,
        itvl_tpl,
        partition_amount);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itg_riemann, TITLE_SOL_RIEMANN, prof);
    fprintf(streamout, "\tPartition amount : %10.0f\n", partition_amount);

    profile_start(prof);
    const polynomial_item_t itg_simpson = integral_poly_simpson(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itg_simpson, TITLE_SOL_SIMPSON, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_riemann - itg_simpson);

    profile_start(prof);
    const polynomial_item_t itgn12_fact_sol = integral_poly_newton_cote_1_2(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itgn12_fact_sol, TITLE_SOL_NC12, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_riemann - itgn12_fact_sol);

    polynomial_destruct(p);
    free(prof);

    return EXIT_SUCCESS;
}
