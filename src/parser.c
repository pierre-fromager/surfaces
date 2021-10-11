
#include "parser.h"

static polynomial_order_t horder;

static int parser_compile(regex_t *r, const char *regex_text)
{
    int status = regcomp(r, regex_text, REG_EXTENDED | REG_NEWLINE);
    if (status != 0)
    {
        char error_message[PARSER_MAX_ERROR_MSG];
        regerror(status, r, error_message, (size_t)PARSER_MAX_ERROR_MSG);
        printf(PARSER_ERR_MSG_COMPILE, regex_text, error_message);
        return 1;
    }
    return 0;
}

static int parser_strpos(char *haystack, char *needle)
{
    char *p = strstr(haystack, needle);
    if (p)
        return (int)(p - haystack);
    return -1;
}

static polynomial_item_t parser_evaluate(char *buff, int xpos)
{
    polynomial_item_t l, r, e;
    char lb[10], rb[10];
    e = 0.0f;
    const int opos = parser_strpos(buff, PARSER_PATTERN_DIV);
    const int mxpos = parser_strpos(buff, PARSER_PATTERN_MINUS);
    const int pxpos = parser_strpos(buff, PARSER_PATTERN_PLUS);
    if (opos >= 1)
    {
        sprintf(lb, PARSER_SUBSTR_FMT, opos, buff);
        sprintf(rb, PARSER_STR_FMT, &(buff[opos + 1]));
        l = (polynomial_item_t)atof(lb);
        r = (polynomial_item_t)atof(rb);
        e = l / r;
    }
    else
        e = (polynomial_item_t)atof(buff);
    if (e == 0.0f)
    {
        if (xpos == 0 || (pxpos == 0 && xpos == 1))
            e = 1.0f;
        if (mxpos == 0)
            e = -1.0f;
    }
    return e;
}

static int parse_poly_member(char *sub, polynomial_t *p)
{
    polynomial_item_t v, acc;
    polynomial_order_t o = 0;
    acc = v = 0;
    char buff[40];
    const int xpos = parser_strpos(sub, PARSER_PATTERN_X);
    const int epos = parser_strpos(sub, PARSER_PATTERN_EXP);
    if (xpos != -1 && epos != -1)
    {
        sprintf(buff, PARSER_SUBSTR_FMT, xpos, sub);
        v = parser_evaluate(buff, xpos);
        if (v == 0.0f)
            v++;
        sprintf(buff, PARSER_STR_FMT, &(sub[epos + 1]));
        o = (polynomial_order_t)atoi(buff);
    }
    else if (xpos != -1)
    {
        o = 1;
        sprintf(buff, PARSER_SUBSTR_FMT, xpos, sub);
        v = parser_evaluate(buff, xpos);
    }
    else
    {
        sprintf(buff, PARSER_STR_FMT, sub);
        v = parser_evaluate(buff, xpos);
    }
    horder = (o > horder) ? o : horder;
    acc = polynomial_getfactor(o, p);
    acc += v;
    polynomial_setfactor(o, acc, p);
    return 0;
}

static int parser_match(regex_t *r, char *eq, polynomial_t *p)
{
    int i, start, finish;
    const char *pc = eq;
    char sub[PARSER_MEMBER_MAX_LEN];
    const int n_matches = PARSER_TERMS_MAX_MATCHES;
    regmatch_t m[PARSER_TERMS_MAX_MATCHES];
    horder = 0;
    while (1)
    {
        i = 0;
        const int nomatch = regexec(r, pc, (size_t)n_matches, m, 0);
        if (nomatch != 0)
            return nomatch;
        for (i = 0; i < n_matches; i++)
        {
            if (m[i].rm_so == -1)
                break;
            if (i != 0)
            {
                start = (int)m[i].rm_so + (int)(pc - eq);
                finish = (int)m[i].rm_eo + (int)(pc - eq);
                sprintf(sub, PARSER_SUBSTR_FMT, (finish - start), eq + start);
                parse_poly_member(sub, p);
            }
        }
        pc += m[0].rm_eo;
    }
    return 0;
}

int parser_parse(char *eq, polynomial_t *p)
{
    int err;
    regex_t r;
    polynomial_t *p_tmp;
    polynomial_order_t cpto;
    err = parser_compile(&r, PARSER_TERMS_PATTERN);
    if (err == 0)
        parser_match(&r, eq, p);
    regfree(&r);
    p_tmp = malloc(sizeof(polynomial_t));
    polynomial_construct(horder + 1, p_tmp);
    for (cpto = 0; cpto < horder + 1; cpto++)
        polynomial_setfactor(cpto, polynomial_getfactor(cpto, p), p_tmp);
    p_tmp->order = horder + 1;
    p = p_tmp;
    polynomial_destruct(p_tmp);
    free(p_tmp);
    return err;
}