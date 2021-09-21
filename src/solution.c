
#include "solution.h"

void print_sol(FILE *streamout, linear_fn_t lf, interval_t li, double sol)
{
    fprintf(streamout, SOL_EQ_FMT, LFN, lf.s, lf.o);
    fprintf(streamout, SOL_ITGR_LIM, ITGFN, li.l, li.h);
    fprintf(streamout, SOL_RES, ITGFN, SYM_ITGR, LFN, sol, ITGR_UA);
    fprintf(streamout, "\n");
}