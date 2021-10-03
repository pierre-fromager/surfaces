
#include "suite_derivative.h"

polynomial_t *psrc;
polynomial_t *pdst;

void reset_test_derivative()
{
}

static int suite_setup(void)
{
    psrc = malloc(sizeof(polynomial_t));
    pdst = malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    polynomial_destruct(psrc);
    polynomial_destruct(pdst);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_derivative_derivate_o0, "derivate_o0"},
    {test_surfaces_derivative_antiderivate_o0, "antiderivate_o0"},
    {test_surfaces_derivative_derivate_o1, "derivate_o1"},
    {test_surfaces_derivative_derivate_o1, "derivate_o2"},
    {test_surfaces_derivative_derivate_o3, "derivate_o3"},
    {0, 0},
};

void test_surfaces_derivative_add_suite()
{
    const char *suite_name = "derivative";
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

void test_surfaces_derivative_derivate_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 10.0f;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, psrc), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    // y = 10 => y' = 0
    polynomial_setfactor(0, ev, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), ev);
    derivative_derivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getorder(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(0, psrc), iocpt);
    for (iocpt = 1; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(0, pdst), iocpt);
    for (iocpt = 1; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pdst), 0);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 0);
}

void test_surfaces_derivative_antiderivate_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 10.0f;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, psrc), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    // y = 10 => Y = 10x
    polynomial_setfactor(0, ev, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), ev);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(io + 1, pdst), ev);
    solution_equation(stdout, pdst);
    for (iocpt = io + 2; iocpt < 12; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pdst), 0);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), ev * cptv);
}

void test_surfaces_derivative_derivate_o1()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 1;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, psrc), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    // y = x => y' = 1
    polynomial_setfactor(1, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    derivative_derivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 1.0f);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 1);
    // y = x + 1 => y' = 1
    polynomial_setfactor(0, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 1);
    // y = 2x + 5 => y' = 2
    polynomial_setfactor(1, 2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2);
    // y = -2x + 5 => y' = -2
    polynomial_setfactor(1, -2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), -2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), -2);
}

void test_surfaces_derivative_derivate_o2()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 2;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, psrc), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    // y = x² => y' = 2x
    polynomial_setfactor(2, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    // y = x² + 1 => y' = 2x
    polynomial_setfactor(0, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    // y = x² + 5 => y' = 2x
    polynomial_setfactor(0, 5.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 5);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    // y = 2x² + 5 => y' = 4x
    polynomial_setfactor(2, 2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 4 * cptv);
    // y = 2x² + x + 5 => y' = 4x + 1
    polynomial_setfactor(1, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 4 * cptv + 1);
}

void test_surfaces_derivative_derivate_o3()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 3;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, psrc), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    // y = x³ => y' = 3x²
    polynomial_setfactor(3, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 3 * cptv * cptv);
    // y = x³ + 1 => y' = 3x²
    polynomial_setfactor(0, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 3 * cptv * cptv);
    // y = 2x³ + 1 => y' = 6x²
    polynomial_setfactor(3, 2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 6 * cptv * cptv);
    // y = 2x³ + x² + x + 1 => y' = 6x² + 2x + 1
    polynomial_setfactor(1, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    polynomial_setfactor(2, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(
            polynomial_calc(cptv, pdst),
            (6 * cptv * cptv) + (2 * cptv) + 1);
}
