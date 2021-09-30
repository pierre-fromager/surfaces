
#include "suite_integral.h"

polynomial_t *pol;
interval_t iv;

void reset_test_integral()
{
    iv = (interval_t){.l = IL_L, .h = IL_H};
}

static int suite_setup(void)
{
    pol = malloc(sizeof(polynomial_t));
    iv = (interval_t){.l = IL_L, .h = IL_H};
    return 0;
}

static int suite_teardown(void)
{
    polynomial_destruct(pol);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_integral_trapez_o0, "integral_trapez_o0"},
    {test_surfaces_integral_midpnt_o0, "integral_midpnt_o0"},
    {test_surfaces_integral_trapez_o1, "integral_trapez_o1"},
    {test_surfaces_integral_midpnt_o1, "integral_midpnt_o1"},
    /*{test_surfaces_integral_o1, "integral_o1"},
    {test_surfaces_integral_o2, "integral_o2"},
    {test_surfaces_integral_o3, "integral_o3"},*/
    {0, 0},
};

void test_surfaces_integral_add_suite()
{
    const char *suite_name = "integral";
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

void test_surfaces_integral_trapez_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = 10
    polynomial_setfactor(io, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = k => (-ev < k < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_trapez(pol, iv), (iv.h - iv.l) * cptv);
    }
}

void test_surfaces_integral_midpnt_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;    
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = 10
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_midpnt(pol, iv), (iv.h - iv.l) * cptv);
    }
}

void test_surfaces_integral_trapez_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    // y = cptv * x => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_trapez(pol, iv), expected * cptv);
    }
    // y = x + 10    
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_trapez(pol, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_trapez(pol, iv), expected2xplusten);
}

void test_surfaces_integral_midpnt_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;    
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    // y = cptv => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_midpnt(pol, iv), expected * cptv);
    }
    // y = x + 10    
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_midpnt(pol, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_midpnt(pol, iv), expected2xplusten);
}

void test_surfaces_integral_o1()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 1;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 1);
    // y = x + 1
    polynomial_setfactor(0, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 1);
    // y = 2x + 5
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 2);
    // y = -2x + 5
    polynomial_setfactor(1, -2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), -2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), -2);
}

void test_surfaces_integral_o2()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 2;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x²
    polynomial_setfactor(2, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 2 * cptv);
    // y = x² + 1
    polynomial_setfactor(0, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 2 * cptv);
    // y = x² + 5
    polynomial_setfactor(0, 5.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 5);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 2 * cptv);
    // y = 2x² + 5
    polynomial_setfactor(2, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pol), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 4 * cptv);
    // y = 2x² + x + 5
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 4 * cptv + 1);
}

void test_surfaces_integral_o3()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 3;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x³
    polynomial_setfactor(3, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 3 * cptv * cptv);
    // y = x³ + 1
    polynomial_setfactor(0, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 3 * cptv * cptv);
    // y = 2x³ + 1
    polynomial_setfactor(3, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pol), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, pol), 6 * cptv * cptv);
    // y = 2x³ + x² + x + 1
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1);
    polynomial_setfactor(2, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pol), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(
            polynomial_calc(cptv, pol),
            (6 * cptv * cptv) + (2 * cptv) + 1);
}
