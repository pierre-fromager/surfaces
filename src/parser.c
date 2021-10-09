
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

static int parse_members(char *sub)
{
    if (strstr(sub, PARSER_PATTERN_X_EXP))
    {
        printf("a*x^e:%s\n", sub);
    }
    else if (strstr(sub, PARSER_PATTERN_X_SINGLE))
    {
        printf("a*x:%s\n", sub);
    }
    else
    {
        printf("k:%s\n", sub);
    }
    return 0;
}

static int parser_match(regex_t *r, char *eq, polynomial_t *p)
{
    int i, start, finish;
    const char *pc = eq;
    char sub[PARSER_MEMBER_MAX_LEN];
    const int n_matches = PARSER_TERMS_MAX_MATCHES;
    regmatch_t m[PARSER_TERMS_MAX_MATCHES];
    if (p)
    {
    }
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
                sprintf(sub, "'%.*s'", (finish - start), eq + start);
                parse_members(sub);
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
    err = parser_compile(&r, PARSER_TERMS_PATTERN);
    if (err == 0)
        parser_match(&r, eq, p);
    regfree(&r);
    return err;
}