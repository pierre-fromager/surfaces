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

#define TITLE_SOL_SITZM "Factory o1"
#define TITLE_SOL_MPTM "Factory o1 interval %u"
#define TITLE_SOL_IL "Factory o1 sum previous intervals"
#define TITLE_SOL_RIEMANN_LEFT "Riemann sum left"
#define TITLE_SOL_RIEMANN_RIGHT "Riemann sum right"
#define TITLE_SOL_RIEMANN_RECT "Riemann sum rectangle"
#define TITLE_SOL_RIEMANN_TRAP "Riemann sum trapezoid"
#define TITLE_SOL_RIEMANN_MP "Riemann sum middle point"
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
#define POLY_MAX_ORDER 128

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

    polynomial_construct(POLY_MAX_ORDER, p);
    int parser_err;
    parser_err = (argc == 2) ? parser_parse(argv[1], p) : parser_parse("1/2x+3", p);
    if (parser_err != 0)
        printf("%s\n", "Parser compilation failed.");
    else
        solution_equation(streamout, p);

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

    const polynomial_item_t itg_ref = integral_poly_reference(p, itvl_tpl);
    const polynomial_item_t partition_amount = 4.0f;

    fprintf(streamout, "\nAntiderivative F(h) - F(l) = %Lf\n", itg_ref);
    fprintf(streamout, "Riemann sum nb rectangles = %Lf\n", partition_amount);

    profile_start(prof);
    const polynomial_item_t riemann_sum_left = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_left);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, riemann_sum_left, TITLE_SOL_RIEMANN_LEFT, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - riemann_sum_left);

    profile_start(prof);
    const polynomial_item_t riemann_sum_right = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_right);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, riemann_sum_right, TITLE_SOL_RIEMANN_RIGHT, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - riemann_sum_right);

    profile_start(prof);
    const polynomial_item_t riemann_sum_rect = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_rectangle);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, riemann_sum_rect, TITLE_SOL_RIEMANN_RECT, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - riemann_sum_rect);

    profile_start(prof);
    const polynomial_item_t riemann_sum_trap = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_trapezoid);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, riemann_sum_trap, TITLE_SOL_RIEMANN_TRAP, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - riemann_sum_trap);

    profile_start(prof);
    const polynomial_item_t riemann_sum_mp = integral_factory_riemann(
        p,
        itvl_tpl,
        partition_amount,
        riemann_middle_point);
    profile_stop(prof);
    solution_print(streamout, p, itvl_tpl, riemann_sum_mp, TITLE_SOL_RIEMANN_MP, prof);
    fprintf(streamout, EPSILON_FMT, INTEG_EPSILON, itg_ref - riemann_sum_mp);

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
    free(p);
    free(prof);

    return EXIT_SUCCESS;
}
