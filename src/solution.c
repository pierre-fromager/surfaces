
#include "solution.h"

static void solution_equation(FILE *streamout, polynomial_t *p)
{
    unsigned c;
    fprintf(streamout, "\n\t%s=",SOL_FN);
    for (c = 0; c < p->order + 1; c++)
        if (polynomial_getfactor(c, p) != 0.0f)
        {
            fprintf(streamout, "%0.4fx^%u", p->factors[c], c);
            if (c < p->order)
                fprintf(streamout, "+");
        }
    fprintf(streamout, "\n");
}

void solution_print(FILE *streamout, polynomial_t *p, interval_t li, polynomial_item_t sol, char *title)
{
    fprintf(streamout, "%s\n", title);
    solution_equation(streamout, p);
    fprintf(streamout, "\t" SOL_ITGR_LIM, SOL_ITGFN, li.l, li.h);
    fprintf(streamout, "\t" SOL_RES, SOL_ITGFN, SYM_ITGR, SOL_FN, sol, ITGR_UA);
    fprintf(streamout, "\n");
}