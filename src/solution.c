
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
    polynomial_order_t c;
    polynomial_order_t oc = 0;
    char factor_buff[SOL_FMT_BUFF_LEN];
    fprintf(streamout, SOL_LF SOL_TAB "%s = ", SOL_FN);
    for (c = 0; c < p->order + 1; c++)
        if (polynomial_getfactor(c, p) != 0.0f)
            oc++;
    if (oc > 0)
    {
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
                solution_format_double(factor_buff, SOL_DOUBLE_FMT_DISPLAY_LEN);
                if (strcmp(factor_buff, "1") == 0 && c != 0)
                    factor_buff[0] = SOL_NULL_CHAR;
                fprintf(streamout, fmt, sign, factor_buff, c);
            }
    }
    else
        fprintf(streamout, "0");
    fprintf(streamout, SOL_LF);
}

void solution_print(
    FILE *streamout,
    polynomial_t *p,
    interval_t li,
    char *result,
    char *title,
    profile_t *prof,
    unsigned int precision)
{
    char fmt_iv_l[SOL_FMT_BUFF_LEN];
    char fmt_iv_h[SOL_FMT_BUFF_LEN];
    char fmt_iv[SOL_FMT_BUFF_LEN];
    char fmt_elapse[SOL_FMT_BUFF_LEN];
    fprintf(streamout, SOL_LF "%s", title);
    solution_equation(streamout, p);
    fprintf(streamout, "\tHigher order %u\n", p->order);
    snprintf(fmt_iv_l, sizeof(char) * 10, SOL_DOUBLE_FMT, li.l);
    solution_format_double(fmt_iv_l, SOL_DOUBLE_FMT_DISPLAY_LEN);
    snprintf(fmt_iv_h, sizeof(char) * 10, SOL_DOUBLE_FMT, li.h);
    solution_format_double(fmt_iv_h, SOL_DOUBLE_FMT_DISPLAY_LEN);
    snprintf(fmt_iv, sizeof(char) * 25, SOL_ITGR_LIM, fmt_iv_l, fmt_iv_h);
    fprintf(streamout, SOL_RES, SYM_ITGR, SOL_FN, fmt_iv, result);
    snprintf(
        fmt_elapse,
        sizeof(char) * SOL_FMT_BUFF_LEN,
        SOL_DOUBLE_FMT,
        (long double)profile_elapse(prof));
    solution_format_double(fmt_elapse, 10);
    fprintf(streamout, SOL_TAB "Precision %u bits" SOL_LF, precision);
    fprintf(streamout, SOL_TAB "Elapse %s s" SOL_LF, fmt_elapse);
}