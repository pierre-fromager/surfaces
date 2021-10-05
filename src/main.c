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
#include "integral.h"
#include "solution.h"
#include "profile.h"

#define TITLE_SOL_SITZM "Factory o1"
#define TITLE_SOL_MPTM "Factory o1 interval %u"
#define TITLE_SOL_IL "Factory o1 sum previous intervals"
#define TITLE_SOL_RIEMANN "Riemann iterative method ε ref"
#define TITLE_SOL_SIMPSON "Simpson method"
#define TITLE_SOL_NC12 "Newton-cote-1-2 method"
#define EPSILON_FMT "\t%s %Lf\n"
#define FN0_S 0.5f
#define FN0_O 3.0f
#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP
#define __ACCURA 16.0f
#define __ACBASE 10.0f

arguments_t args;

static void set_multiple_intervals(intervals_t itvls, interval_t itvl_tpl)
{
    itvls[0] = itvls[1] = itvl_tpl;
    itvls[0].h = itvls[1].l = (itvls[0].l + itvls[0].h) / 2;
}

static polynomial_item_t factory_intervals(
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
        sol = integral_factory(p, itvls[itvlcpt]);
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

    const interval_t itvl_tpl = {.l = IL_L, .h = IL_H};
    profile_start(prof);
    const polynomial_item_t sol_o1 = integral_factory(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, sol_o1, TITLE_SOL_SITZM, prof);

    const unsigned nbivs = 2;
    intervals_t itvls = malloc(sizeof(interval_t) * nbivs);
    set_multiple_intervals(itvls, itvl_tpl);
    const polynomial_item_t sol_m01 = factory_intervals(p, itvls, nbivs, prof);
    free(itvls);
    solution_print(streamout, p, itvl_tpl, sol_m01, TITLE_SOL_IL, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, sol_o1 - sol_m01);

    // y = x^3 + 1/2x + 3
    polynomial_construct(3, p);
    polynomial_setfactor(0, FN0_O, p);
    polynomial_setfactor(1, FN0_S, p);
    polynomial_setfactor(3, 1.0f, p);
    const polynomial_item_t itg_ref = integral_poly_reference(p, itvl_tpl);
    const polynomial_item_t partition_amount = 4.0f;
    profile_start(prof);
    const polynomial_item_t itg_riemann = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_right);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itg_riemann, TITLE_SOL_RIEMANN, prof);
    fprintf(streamout, "\tPartition amount : %Lf\n", partition_amount);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - itg_riemann);

    profile_start(prof);
    const polynomial_item_t itg_simpson = integral_poly_simpson(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itg_simpson, TITLE_SOL_SIMPSON, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - itg_simpson);

    profile_start(prof);
    const polynomial_item_t itgn12_fact_sol = integral_poly_newton_cote_1_2(p, itvl_tpl);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, itgn12_fact_sol, TITLE_SOL_NC12, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - itgn12_fact_sol);

    polynomial_destruct(p);
    free(prof);

    return EXIT_SUCCESS;
}
