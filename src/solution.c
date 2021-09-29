
#include "solution.h"

void solution_format_double(char *s, unsigned n)
{
    char *p;
    unsigned count;
    p = strchr(s, SOL_DOT_CHAR);
    if (p != NULL)
    {
        count = n;
        while (count != 0)
        {
            count--;
            if (*p == SOL_NULL_CHAR)
                break;
            p++;
        }
        *p-- = SOL_NULL_CHAR;
        while (*p == '0')
            *p-- = SOL_NULL_CHAR;
        if (*p == SOL_DOT_CHAR)
            *p = SOL_NULL_CHAR;
    }
}

void solution_equation(FILE *streamout, polynomial_t *p)
{
    unsigned c;
    char factor_buff[SOL_FMT_BUFF_LEN];
    fprintf(streamout, "\n\t%s = ", SOL_FN);
    for (c = 0; c < p->order + 1; c++)
        if (polynomial_getfactor(c, p) != 0.0f)
        {
            const char *sign = (polynomial_getfactor(c, p) < 0) ? "" : "+";
            const char *fmto = (c == 0) ? "%s%s" : "%s%sx";
            const char *fmt = (c > 1) ? "%s%sx^%u" : fmto;
            snprintf(
                factor_buff,
                sizeof(char) * SOL_FMT_BUFF_LEN,
                SOL_DOUBLE_FMT,
                polynomial_getfactor(c, p));
            solution_format_double(factor_buff, 5);
            if (strcmp(factor_buff, "1") == 0)
                factor_buff[0] = SOL_NULL_CHAR;
            fprintf(streamout, fmt, sign, factor_buff, c);
        }
    fprintf(streamout, "\n");
}

void solution_print(FILE *streamout, polynomial_t *p, interval_t li, polynomial_item_t sol, char *title)
{
    char fmt_buff[SOL_FMT_BUFF_LEN];
    char fmt_iv_l[SOL_FMT_BUFF_LEN];
    char fmt_iv_h[SOL_FMT_BUFF_LEN];
    fprintf(streamout, "%s\n", title);
    solution_equation(streamout, p);
    snprintf(fmt_iv_l, sizeof(char) * SOL_FMT_BUFF_LEN, SOL_DOUBLE_FMT, li.l);
    solution_format_double(fmt_iv_l, 5);
    snprintf(fmt_iv_h, sizeof(char) * SOL_FMT_BUFF_LEN, SOL_DOUBLE_FMT, li.h);
    solution_format_double(fmt_iv_h, 5);
    fprintf(streamout, "\t" SOL_ITGR_LIM, SOL_ITGFN, fmt_iv_l, fmt_iv_h);
    snprintf(fmt_buff, sizeof(char) * SOL_FMT_BUFF_LEN, SOL_DOUBLE_FMT, sol);
    solution_format_double(fmt_buff, 5);
    fprintf(streamout, "\t" SOL_RES, SOL_ITGFN, SYM_ITGR, SOL_FN, fmt_buff, ITGR_UA);
    fprintf(streamout, "\n");
}