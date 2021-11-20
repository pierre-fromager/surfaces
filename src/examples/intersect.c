/**
 * @file expolysurf.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief find intersection(s) for 2 polynomials
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "polynomial.h"
#include "libpolysurf.h"

#define POLY_MAX_ORDER 4096
#define NB_ARGS_REQ 2
#define POINT_FMT "p%u(%.16Lf , %.16Lf)\n"
#define ERR_P_REQ_MSG "Missing : 2 arguments required %d provided.\n"
#define PARSE_ERR_MSG "Error parsing %s \n"
#define MSG_NO_INTER "No intersection\n"

static void resizepol(polynomial_t *p)
{
    polynomial_item_t *facts;
    polynomial_ratio_t *ratios;
    facts = NULL;
    facts = realloc(p->factors, sizeof(polynomial_item_t) * (p->order + 1));
    if (facts != NULL)
        p->factors = facts;
    ratios = NULL;
    ratios = realloc(p->fratios, sizeof(polynomial_ratio_t) * (p->order + 1));
    if (ratios != NULL)
        p->fratios = ratios;
}

static void freepol(polynomial_t *p)
{
    polynomial_destruct(p);
    free(p);
}

static void parse(FILE *streamout, polynomial_t *p, char *pstring)
{
    if (parser_parse(pstring, p))
    {
        fprintf(streamout, PARSE_ERR_MSG, pstring);
        freepol(p);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    FILE *streamout = stdout;
    if (argc < NB_ARGS_REQ + 1)
    {
        fprintf(streamout, ERR_P_REQ_MSG, argc - 1);
        return EXIT_FAILURE;
    }
    polynomial_t *p1, *p2;
    p1 = (polynomial_t *)malloc(sizeof(polynomial_t));
    polynomial_construct(POLY_MAX_ORDER, p1);
    parse(streamout, p1, argv[1]);
    resizepol(p1);
    p2 = (polynomial_t *)malloc(sizeof(polynomial_t));
    polynomial_construct(POLY_MAX_ORDER, p2);
    parse(streamout, p2, argv[2]);
    resizepol(p2);
    coord_t *coords;
    const interval_t ivl = (interval_t){.l = -50, .h = 50};
    const polynomial_order_t ho = (p1->order > p2->order) ? p1->order : p2->order;
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    const polynomial_order_t nbr = polysurf_intersect(p1, p2, ivl, coords);
    polynomial_order_t ito;
    if (nbr)
        for (ito = 0; ito < nbr; ito++)
            fprintf(
                streamout,
                POINT_FMT,
                ito,
                (*(coords + ito)).x,
                (*(coords + ito)).y);
    else
        fprintf(streamout, MSG_NO_INTER);

    free(coords);
    freepol(p2);
    freepol(p1);
    return EXIT_SUCCESS;
}