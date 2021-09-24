
#include "suite_polynomial.h"

polynomial_t *p;
//const polynomial_item_t iv = 0.0f;

void reset_test_polynomial()
{
}

static int suite_setup(void)
{
    p = malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    polynomial_destruct(p);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_polynomial_o0, "polynomial_o0"},
    {test_surfaces_polynomial_o1, "polynomial_o1"},
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

void test_surfaces_polynomial_o0()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 0;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    // y = 0
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);
    // y = 10
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), ev);
}

void test_surfaces_polynomial_o1()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 1;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(sizeof(p->factors), 8);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);
    // y = x
    polynomial_setfactor(0, 0.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv);
    // y = x + 1
    polynomial_setfactor(0, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv + 1);
    // y = x + 5
    polynomial_setfactor(0, 5.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 5);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv + 5);
    // y = 2x + 5
    polynomial_setfactor(1, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), 2 * cptv + 5);
    // y = -2x + 5
    polynomial_setfactor(1, -2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), -2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), -2 * cptv + 5);
}
