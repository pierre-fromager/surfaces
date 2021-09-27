
#include "solution.h"

void solution_equation(FILE *streamout, polynomial_t *p)
{
    unsigned c;
    fprintf(streamout, "\n\t%s = ", SOL_FN);
    for (c = 0; c < p->order + 1; c++)
        if (polynomial_getfactor(c, p) != 0.0f)
        {
            const char *sign = (polynomial_getfactor(c, p) < 0) ? "" : "+";
            const char *fmto = (c == 0) ? "%s%0.4f" : "%s%0.4fx";
            const char *fmt = (c > 1) ? "%s%0.4fx^%u" : fmto;
            fprintf(streamout, fmt, sign, polynomial_getfactor(c, p), c);
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