
#include "suite_polynomial.h"

polynomial_t *poly;

void reset_test_polynomial()
{
}

static int suite_setup(void)
{
    poly = malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    polynomial_destruct(poly);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_polynomial_init, "polynomial_init"},
    {0, 0},
};

void test_surfaces_polynomial_add_suite()
{
    const char *suite_name = "polynomial";
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

void test_surfaces_polynomial_init()
{
    const double iv = 0.0f;
    const double ev = 10.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(poly);
    polynomial_construct(10, poly);
    double r0 = polynomial_calc(iv, poly);
    CU_ASSERT_EQUAL(r0, iv);
    *(poly->factors + 0) = ev;
    CU_ASSERT_EQUAL(*(poly->factors + 0), ev);
    double r1 = polynomial_calc(1.0f, poly);
    CU_ASSERT_EQUAL(r1, ev);
}
