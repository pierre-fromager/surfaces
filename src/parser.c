
#include "parser.h"

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

static polynomial_item_t parser_evaluate(char *buff, int xpos, polynomial_order_t o, polynomial_t *p)
{
    int num, denom;
    polynomial_item_t e;
    char lb[10], rb[10];
    const int dpos = parser_strpos(buff, PARSER_PATTERN_DIV);
    const int mxpos = parser_strpos(buff, PARSER_PATTERN_MINUS);
    const int pxpos = parser_strpos(buff, PARSER_PATTERN_PLUS);
    e = 0.0f;
    if (dpos >= 1)
    {
        sprintf(lb, PARSER_SUBSTR_FMT, dpos, buff);
        sprintf(rb, PARSER_STR_FMT, &(buff[dpos + 1]));
        num = atoi(lb);
        denom = atoi(rb);
        polynomial_addratio(o, (polynomial_ratio_t){.num = num, .denom = denom}, p);
        e = (polynomial_item_t)num / (polynomial_item_t)denom;
    }
    else
    {
        e = (polynomial_item_t)atof(buff);
        // we don't want to get a fraction from a real because costly
        // so don't mix real and fractions, tests will run in that direction.
        if (fmodl(e, 1.0f) == 0)
            polynomial_addratio(o, (polynomial_ratio_t){.num = (int)e, .denom = 1}, p);
    }

    if (e == 0.0f)
    {
        if (xpos == 0 || (pxpos == 0 && xpos == 1))
        {
            e = 1.0f;
            if (o > 0)
                polynomial_addratio(o, (polynomial_ratio_t){.num = 1, .denom = 1}, p);
        }
        if (mxpos == 0)
        {
            e = -1.0f;
            if (o > 0)
                polynomial_addratio(o, (polynomial_ratio_t){.num = -1, .denom = 1}, p);
        }
    }
    return e;
}

static int parse_poly_member(char *sub, polynomial_t *p)
{
    polynomial_item_t v, acc;
    polynomial_order_t o;
    acc = v = 0;
    char buff[40];
    const int xpos = parser_strpos(sub, PARSER_PATTERN_X);
    const int epos = parser_strpos(sub, PARSER_PATTERN_EXP);

    if (xpos != -1 && epos != -1)
    {
        sprintf(buff, PARSER_STR_FMT, &(sub[epos + 1]));
        o = (polynomial_order_t)atoi(buff);
        sprintf(buff, PARSER_SUBSTR_FMT, xpos, sub);
        v = parser_evaluate(buff, xpos, o, p);
        if (v == 0.0f)
            v++;
    }
    else if (xpos != -1)
    {
        o = 1;
        sprintf(buff, PARSER_SUBSTR_FMT, xpos, sub);
        v = parser_evaluate(buff, xpos, o, p);
    }
    else
    {
        o = 0;
        sprintf(buff, PARSER_STR_FMT, sub);
        v = parser_evaluate(buff, xpos, o, p);
    }
    p->order = (o > p->order) ? o : p->order;
    acc = polynomial_getfactor(o, p);
    acc += v;
    polynomial_setfactor(o, acc, p);
    return 0;
}

static int parser_match(regex_t *r, char *eq, polynomial_t *p)
{
    int i, start, finish;
    i = start = finish = 0;
    const char *pc = eq;
    char sub[PARSER_MEMBER_MAX_LEN];
    const int n_matches = PARSER_TERMS_MAX_MATCHES;
    regmatch_t m[PARSER_TERMS_MAX_MATCHES];
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
    p->order = 0;
    err = parser_compile(&r, PARSER_TERMS_PATTERN);
    if (err == 0)
        parser_match(&r, eq, p);
    regfree(&r);

    return err;
}