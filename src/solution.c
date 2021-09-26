
#include "solution.h"

void print_sol(FILE *streamout, linear_fn_t lf, interval_t li, double sol, char *title)
{
    fprintf(streamout, "%s\n", title);
    fprintf(streamout, "\t" SOL_EQ_FMT, LFN, lf.s, lf.o);
    fprintf(streamout, "\t" SOL_ITGR_LIM, ITGFN, li.l, li.h);
    fprintf(streamout, "\t" SOL_RES, ITGFN, SYM_ITGR, LFN, sol, ITGR_UA);
    fprintf(streamout, "\n");
}