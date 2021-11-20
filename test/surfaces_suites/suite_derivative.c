
#include "suite_derivative.h"

static polynomial_t *psrc;
static polynomial_t *pdst;
static const double granularity = 0.00001f;

void reset_test_derivative()
{
    polynomial_destruct(psrc);
    polynomial_destruct(pdst);
}

static int suite_setup(void)
{
    psrc = (polynomial_t *)malloc(sizeof(polynomial_t));
    pdst = (polynomial_t *)malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    free(psrc);
    free(pdst);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_derivative_derivate_o0, "derivate_o0"},
    {test_surfaces_derivative_derivate_o1, "derivate_o1"},
    {test_surfaces_derivative_derivate_o1, "derivate_o2"},
    {test_surfaces_derivative_derivate_o3, "derivate_o3"},
    {test_surfaces_derivative_antiderivate_o0, "antiderivate_o0"},
    {test_surfaces_derivative_antiderivate_o1, "antiderivate_o1"},
    {test_surfaces_derivative_antiderivate_o2, "antiderivate_o2"},
    {test_surfaces_derivative_antiderivate_o3, "antiderivate_o3"},
    {test_surfaces_derivative_antiderivate_o4096, "antiderivate_o4096"},
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
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = 10 => y' = 0
    polynomial_setfactor(0, ev, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), ev);
    derivative_derivate(psrc, pdst);
    CU_ASSERT_EQUAL(pdst->order, 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(0, pdst), 0.0f, granularity);
    for (iocpt = 1; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 1; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pdst), 0);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_DOUBLE_EQUAL(polynomial_calc(cptv, pdst), 0.0f, granularity);

    const polynomial_ratio_t r = polynomial_getratio(io, pdst);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);

    reset_test_derivative();
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
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x => y' = 1
    polynomial_setfactor(1, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    derivative_derivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 1.0f);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 1);
    polynomial_destruct(pdst);
    // y = x + 1 => y' = 1
    polynomial_setfactor(0, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 1);
    polynomial_destruct(pdst);
    // y = 2x + 5 => y' = 2
    polynomial_setfactor(1, 2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2);
    polynomial_destruct(pdst);
    // y = -2x + 5 => y' = -2
    polynomial_setfactor(1, -2.0f, psrc);
    polynomial_setratio(1, -2, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), -2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), -2);

    const polynomial_ratio_t r = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r.num, -2);
    CU_ASSERT_EQUAL(r.denom, 1);

    reset_test_derivative();
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
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x² => y' = 2x
    polynomial_setfactor(2, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    polynomial_destruct(pdst);
    // y = x² + 1 => y' = 2x
    polynomial_setfactor(0, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    polynomial_destruct(pdst);
    // y = x² + 5 => y' = 2x
    polynomial_setfactor(0, 5.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 5);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 2 * cptv);
    polynomial_destruct(pdst);
    // y = 2x² + 5 => y' = 4x
    polynomial_setfactor(2, 2.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 4 * cptv);
    polynomial_destruct(pdst);
    // y = 2x² + x + 5 => y' = 4x + 1
    polynomial_setfactor(1, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), 4 * cptv + 1);

    const polynomial_ratio_t r0 = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r0.num, 1);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, pdst);
    CU_ASSERT_EQUAL(r1.num, 4);
    CU_ASSERT_EQUAL(r1.denom, 1);

    reset_test_derivative();
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
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x³ => y' = 3x²
    // by factor
    polynomial_setfactor(3, 1.0f, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), io * cptv * cptv);
    polynomial_destruct(pdst);
    // by ratio
    polynomial_setratio(3, 1, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getratio(3, psrc).num, 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), io * cptv * cptv);
    polynomial_destruct(pdst);
    // y = x³ + 1 => y' = 3x²
    polynomial_setfactor(0, 1.0f, psrc);
    polynomial_setratio(0, 1, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), io * cptv * cptv);
    polynomial_destruct(pdst);
    // y = 2x³ + 1 => y' = 6x²
    polynomial_setfactor(3, 2.0f, psrc);
    polynomial_setratio(3, 2, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, psrc), 2);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), io * 2 * cptv * cptv);
    polynomial_destruct(pdst);
    // y = 2x³ + x² + x + 1 => y' = 6x² + 2x + 1
    polynomial_setfactor(1, 1.0f, psrc);
    polynomial_setfactor(2, 1.0f, psrc);
    polynomial_setratio(1, 1, 1, psrc);
    polynomial_setratio(2, 1, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 1);
    derivative_derivate(psrc, pdst);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(
            polynomial_calc(cptv, pdst),
            (6 * cptv * cptv) + (2 * cptv) + 1);

    const polynomial_ratio_t r0 = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r0.num, 1);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, pdst);
    CU_ASSERT_EQUAL(r1.num, 2);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(2, pdst);
    CU_ASSERT_EQUAL(r2.num, 6);
    CU_ASSERT_EQUAL(r2.denom, 1);

    reset_test_derivative();
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
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = 10 => Y = 10x
    polynomial_setfactor(0, ev, psrc);
    polynomial_setratio(0, (int)ev, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), ev);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(io + 1, pdst), ev);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pdst), ev * cptv);

    const polynomial_ratio_t r = polynomial_getratio(io + 1, pdst);
    CU_ASSERT_EQUAL(r.num, ev);
    CU_ASSERT_EQUAL(r.denom, 1);

    reset_test_derivative();
}

void test_surfaces_derivative_antiderivate_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 1.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x => Y = (1/2)x²
    polynomial_setfactor(1, ev, psrc);
    polynomial_setratio(1, 1, 2, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), ev);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(2, pdst), 0.5f, granularity);
    polynomial_destruct(pdst);
    // y = x + 10 => Y = (1/2)x² + 10x
    polynomial_setfactor(0, 10.0f, psrc);
    polynomial_setratio(0, 10, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 10.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(2, pdst), 0.5f, granularity);
    polynomial_destruct(pdst);
    // y = 2x + 10 => Y = x² + 10x
    polynomial_setfactor(1, 2.0f, psrc);
    polynomial_setratio(1, 2, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, psrc), 2.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(2, pdst), 1.0f, granularity);

    const polynomial_ratio_t r0 = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r0.num, 0);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, pdst);
    CU_ASSERT_EQUAL(r1.num, 10);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(2, pdst);
    CU_ASSERT_EQUAL(r2.num, 2);
    CU_ASSERT_EQUAL(r2.denom, 2);

    reset_test_derivative();
}

void test_surfaces_derivative_antiderivate_o2()
{
    const polynomial_order_t io = 2;
    const polynomial_item_t ev = 1.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x² => Y = (1/3)x^3
    polynomial_setfactor(2, ev, psrc);
    polynomial_setratio(2, 1, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), ev);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(3, pdst), 0.333333f, granularity);
    polynomial_destruct(pdst);
    // y = x² + 10 => Y = (1/3)x^3 + 10x
    polynomial_setfactor(0, 10.0f, psrc);
    polynomial_setratio(0, 10, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 10.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(3, pdst), 0.333333f, granularity);
    polynomial_destruct(pdst);
    // y = 3x² + 10 => Y = x^3 + 10x
    polynomial_setfactor(2, 3.0f, psrc);
    polynomial_setratio(2, 3, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, psrc), 3.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(3, pdst), 1.0f, granularity);

    const polynomial_ratio_t r0 = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r0.num, 0);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, pdst);
    CU_ASSERT_EQUAL(r1.num, 10);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(2, pdst);
    CU_ASSERT_EQUAL(r2.num, 0);
    CU_ASSERT_EQUAL(r2.denom, 1);
    const polynomial_ratio_t r3 = polynomial_getratio(3, pdst);
    CU_ASSERT_EQUAL(r3.num, 3);
    CU_ASSERT_EQUAL(r3.denom, 3);

    reset_test_derivative();
}

void test_surfaces_derivative_antiderivate_o3()
{
    const polynomial_order_t io = 3;
    const polynomial_item_t ev = 1.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x³ => Y = (1/4)x^4
    polynomial_setfactor(3, ev, psrc);
    polynomial_setratio(3, 1, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, psrc), 1.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(4, pdst), 0.25f, granularity);
    polynomial_destruct(pdst);
    // y = x³ + 10 => Y = (1/4)x^4 + 10x
    polynomial_setfactor(0, 10.0f, psrc);
    polynomial_setratio(0, 10, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, psrc), 10.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(4, pdst), 0.25f, granularity);
    polynomial_destruct(pdst);
    // y = 4x³ + 10 => Y = x^4 + 10x
    polynomial_setfactor(3, 4.0f, psrc);
    polynomial_setratio(3, 4, 1, psrc);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, psrc), 4.0f);
    derivative_antiderivate(psrc, pdst);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pdst), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pdst), 0.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pdst), 0.0f);
    CU_ASSERT_DOUBLE_EQUAL(polynomial_getfactor(4, pdst), 1.0f, granularity);

    const polynomial_ratio_t r0 = polynomial_getratio(0, pdst);
    CU_ASSERT_EQUAL(r0.num, 0);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, pdst);
    CU_ASSERT_EQUAL(r1.num, 10);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(2, pdst);
    CU_ASSERT_EQUAL(r2.num, 0);
    CU_ASSERT_EQUAL(r2.denom, 1);
    const polynomial_ratio_t r3 = polynomial_getratio(3, pdst);
    CU_ASSERT_EQUAL(r3.num, 0);
    CU_ASSERT_EQUAL(r3.denom, 1);
    const polynomial_ratio_t r4 = polynomial_getratio(4, pdst);
    CU_ASSERT_EQUAL(r4.num, 4);
    CU_ASSERT_EQUAL(r4.denom, 4);

    reset_test_derivative();
}

void test_surfaces_derivative_antiderivate_o4096()
{
    const polynomial_order_t io = 4096;
    polynomial_order_t iocpt;

    CU_ASSERT_PTR_NOT_NULL_FATAL(psrc);
    CU_ASSERT_PTR_NOT_NULL_FATAL(pdst);
    polynomial_construct(io, psrc);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, psrc), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, psrc).denom, 1);
    // y = x^4096 => Y = x^4097
    polynomial_setfactor(io, 1.0f, psrc);
    polynomial_setratio(io, 1, 1, psrc);
    derivative_antiderivate(psrc, pdst);
    const polynomial_ratio_t r4096 = polynomial_getratio(io, pdst);
    CU_ASSERT_EQUAL(r4096.num, 0);
    CU_ASSERT_EQUAL(r4096.denom, 1);
    const polynomial_ratio_t r4097 = polynomial_getratio(io + 1, pdst);
    CU_ASSERT_EQUAL(r4097.num, 1);
    CU_ASSERT_EQUAL(r4097.denom, 4097);
    CU_ASSERT_DOUBLE_EQUAL(
        polynomial_getfactor(io + 1, pdst),
        0.000244f,
        granularity);

    reset_test_derivative();
}
