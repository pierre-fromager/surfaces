
#include "suite_parser.h"

static polynomial_t *p;
static polynomial_order_t ocpt;
static char eq[1024];
static int parser_err;

void reset_test_parser()
{
    polynomial_destruct(p);
}

static int suite_setup(void)
{
    p = (polynomial_t *)malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    free(p);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_parser_o0, "parser_o0"},
    {test_surfaces_parser_o1, "parser_o1"},
    {test_surfaces_parser_o2, "parser_o2"},
    {test_surfaces_parser_o10, "parser_o10"},
    {test_surfaces_parser_o100, "parser_o100"},
    {test_surfaces_parser_o1000, "parser_o1000"},
    {test_surfaces_parser_o4096, "parser_o4096"},
    {0, 0},
};

void test_surfaces_parser_add_suite()
{
    const char *suite_name = "parser";
    const char *suite_err_fmt = "Error adding suite %s : %s\n";
    const char *test_err_fmt = "Error adding test '%s' : %s\n";
    CU_pSuite suite = CU_add_suite(suite_name, suite_setup, suite_teardown);
    if (!suite)
    {
        CU_cleanup_registry();
        printf(suite_err_fmt, suite_name, CU_get_error_msg());
        _exit(3);
    }
    int i;
    for (i = 0; test_functions[i].name; i++)
    {
        if (!CU_add_test(suite, test_functions[i].name, test_functions[i].function))
        {
            CU_cleanup_registry();
            printf(test_err_fmt, test_functions[i].name, CU_get_error_msg());
            _exit(3);
        }
    }
}

void test_surfaces_parser_o0()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = 0
    strcpy(eq, "0");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(p->order, 0);
    polynomial_reset(p);
    // y = 1
    strcpy(eq, "1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 0.5 + 0.5 = 1
    strcpy(eq, "0.5+0.5");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 0.5 - 0.5 = 0
    strcpy(eq, "0.5-0.5");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 2
    strcpy(eq, "2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = -2
    strcpy(eq, "-2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), -2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, -2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1 + 1 = 2
    strcpy(eq, "1+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1 - 1 = 0
    strcpy(eq, "1-1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1 + 2 - 3 = 0
    strcpy(eq, "1+2-3");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1 + 2 - 4 = -1/1 = -1
    strcpy(eq, "1+2-4");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), -1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, -1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1 + 2 + 3 + 4 = 10 (with zeros pointless)
    strcpy(eq, "0+1+2+3+4+0+0+0");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 10);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1/2 = 0.5
    strcpy(eq, "1/2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.5f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 2);
    polynomial_reset(p);
    // y = 1/2 + 0.5 = 1
    strcpy(eq, "1/2+0.5");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 2);
    polynomial_reset(p);
    // y = 1/2 + 1/2 = 1
    strcpy(eq, "1/2+1/2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3 - 1/3 = 0
    strcpy(eq, "1/3-1/3");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1/120 + 119/120 = 1.0f
    strcpy(eq, "1/120+119/120");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    polynomial_reset(p);
    // y = 0.9 + 0.1 = 1.0f
    strcpy(eq, "0.9+0.1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    polynomial_reset(p);
    // y = 1/9 + 9/10 = 1.0f
    strcpy(eq, "1/10+9/10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    polynomial_reset(p);
    // y = 1/9 + 9/10 + 1 = 2.0f
    strcpy(eq, "1/10+9/10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 0);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 2.0f, 64);
    polynomial_reset(p);
    reset_test_parser();
}

void test_surfaces_parser_o1()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x
    strcpy(eq, "x");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    polynomial_reset(p);
    // y = x + 1
    strcpy(eq, "x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    polynomial_reset(p);
    // y = 2x
    strcpy(eq, "2x");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    polynomial_reset(p);
    // y = 2x + x
    strcpy(eq, "2x+x");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x + 2/3x
    strcpy(eq, "1/3x+2/3x");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    reset_test_parser();
}

void test_surfaces_parser_o2()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x^2
    strcpy(eq, "x^2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    polynomial_reset(p);
    // y = x^2 + 1
    strcpy(eq, "x^2+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^2
    strcpy(eq, "2x^2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^2 + x^2
    strcpy(eq, "2x^2+x^2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x^2 + 2/3x^2
    strcpy(eq, "1/3x^2+2/3x^2");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    polynomial_reset(p);
    // y = x^2 + 1/3x + 1
    strcpy(eq, "x^2+1/3x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 2);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1 / 3, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(2, p).denom, 1);
    reset_test_parser();
}

void test_surfaces_parser_o10()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x^10
    strcpy(eq, "x^10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    polynomial_reset(p);
    // y = x^10 + 1
    strcpy(eq, "x^10+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^10
    strcpy(eq, "2x^10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^10 + x^10
    strcpy(eq, "2x^10+x^10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x^10 + 2/3x^10
    strcpy(eq, "1/3x^10+2/3x^10");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    polynomial_reset(p);
    // y = x^10 + 1/3x + 1
    strcpy(eq, "x^10+1/3x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 10);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1 / 3, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(10, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(10, p).denom, 1);
    reset_test_parser();
}

void test_surfaces_parser_o100()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x^100
    strcpy(eq, "x^100");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    polynomial_reset(p);
    // y = x^100 + 1
    strcpy(eq, "x^100+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^100
    strcpy(eq, "2x^100");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^100 + x^100
    strcpy(eq, "2x^100+x^100");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x^100 + 2/3x^100
    strcpy(eq, "1/3x^100+2/3x^100");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    polynomial_reset(p);
    // y = x^100 + 1/3x + 1
    strcpy(eq, "x^100+1/3x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 100);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1 / 3, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(100, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(100, p).denom, 1);
    reset_test_parser();
}

void test_surfaces_parser_o1000()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x^1000
    strcpy(eq, "x^1000");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    polynomial_reset(p);
    // y = x^1000 + 1
    strcpy(eq, "x^1000+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^1000
    strcpy(eq, "2x^1000");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^1000 + x^1000
    strcpy(eq, "2x^1000+x^1000");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x^1000 + 2/3x^1000
    strcpy(eq, "1/3x^1000+2/3x^1000");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    polynomial_reset(p);
    // y = x^1000 + 1/3x + 1
    strcpy(eq, "x^1000+1/3x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 1000);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1 / 3, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(1000, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1000, p).denom, 1);
    reset_test_parser();
}

void test_surfaces_parser_o4096()
{
    const polynomial_order_t io = POLY_MAX_ORDER;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
    // y = x^4096
    strcpy(eq, "x^4096");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    polynomial_reset(p);
    // y = x^4096 + 1
    strcpy(eq, "x^4096+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^4096
    strcpy(eq, "2x^4096");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 2.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 2);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    polynomial_reset(p);
    // y = 2x^4096 + x^4096
    strcpy(eq, "2x^4096+x^4096");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 3.0f);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 3);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    polynomial_reset(p);
    // y = 1/3x^4096 + 2/3x^4096
    strcpy(eq, "1/3x^4096+2/3x^4096");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 0.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    polynomial_reset(p);
    // y = x^4096 + 1/3x + 1
    strcpy(eq, "x^4096+1/3x+1");
    parser_err = parser_parse(eq, p);
    CU_ASSERT_EQUAL(parser_err, 0);
    CU_ASSERT_EQUAL(p->order, 4096);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, p), 1.0f, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(0, p).denom, 1);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(1, p), 1 / 3, 64);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(1, p).denom, 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(4096, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(4096, p).denom, 1);
    reset_test_parser();
}