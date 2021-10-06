
#include "suite_integral.h"

polynomial_t *pol;
interval_t iv;
polynomial_order_t ocpt;
polynomial_item_t cptv;

const double granularity = 0.00001f;

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
    {test_surfaces_integral_ref_o0, "integral_ref_o0"},
    {test_surfaces_integral_trapez_o0, "integral_trapez_o0"},
    {test_surfaces_integral_midpnt_o0, "integral_midpnt_o0"},
    {test_surfaces_integral_simpson_o0, "integral_simpson_o0"},
    {test_surfaces_integral_factory_riemann_o0, "integral_factory_riemann_o0"},
    {test_surfaces_integral_factory_o0, "integral_factory_o0"},
    {test_surfaces_integral_ref_o1, "integral_ref_o1"},
    {test_surfaces_integral_trapez_o1, "integral_trapez_o1"},
    {test_surfaces_integral_midpnt_o1, "integral_midpnt_o1"},
    {test_surfaces_integral_factory_o1, "integral_factory_o1"},
    {test_surfaces_integral_ref_o2, "integral_ref_o2"},
    {test_surfaces_integral_ref_o3, "integral_ref_o3"},
    {test_surfaces_integral_ref_o4, "integral_ref_o4"},
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

void test_surfaces_integral_ref_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
    // y = 10
    polynomial_setfactor(io, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = k => (-ev < k < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_reference(pol, iv), (iv.h - iv.l) * cptv);
    }
}

void test_surfaces_integral_trapez_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
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
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
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

void test_surfaces_integral_simpson_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_simpson(pol, iv), (iv.h - iv.l) * cptv);
    }
}

void test_surfaces_integral_factory_riemann_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t dxi = iv.h - iv.l;
    const polynomial_item_t nbr = 2.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(pol, iv, nbr, riemann_left),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(pol, iv, nbr, riemann_right),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(pol, iv, nbr, riemann_middle_point),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(pol, iv, nbr, riemann_trapezoid),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(pol, iv, nbr, riemann_rectangle),
            dxi * cptv);
    }
}

void test_surfaces_integral_factory_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, pol);
        CU_ASSERT_EQUAL(integral_factory(pol, iv), (iv.h - iv.l) * cptv);
    }
}

void test_surfaces_integral_ref_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    // y = cptv * x => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, pol);
        CU_ASSERT_EQUAL(integral_poly_reference(pol, iv), expected * cptv);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_reference(pol, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_reference(pol, iv), expected2xplusten);
}

void test_surfaces_integral_trapez_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
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
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
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

void test_surfaces_integral_factory_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    // y = cptv => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, pol);
        CU_ASSERT_EQUAL(integral_factory(pol, iv), expected * cptv);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_EQUAL(integral_factory(pol, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_EQUAL(integral_factory(pol, iv), expected2xplusten);
}

void test_surfaces_integral_ref_o2()
{
    const polynomial_order_t io = 2;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
    // y = x²
    polynomial_setfactor(2, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)41.666667f,
        (double)granularity);
    // y = x² + 10
    polynomial_setfactor(0, 10.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)91.666667,
        (double)granularity);
    // y = 2x² + 10
    polynomial_setfactor(2, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)133.333333,
        (double)granularity);
}

void test_surfaces_integral_ref_o3()
{
    const polynomial_order_t io = 3;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
    // y = x³
    polynomial_setfactor(3, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)156.25f,
        (double)granularity);
    // y = x³ + 10
    polynomial_setfactor(0, 10.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)206.25f,
        (double)granularity);
    // y = 2x³ + 10
    polynomial_setfactor(3, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)362.5f,
        (double)granularity);
}

void test_surfaces_integral_ref_o4()
{
    const polynomial_order_t io = 4;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, pol), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, pol), 0);
    // y = x⁴
    polynomial_setfactor(io, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)625.0f,
        (double)granularity);
    // y = x⁴ + 10
    polynomial_setfactor(0, 10.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)675.0f,
        (double)granularity);
    // y = 2x⁴ + 10
    polynomial_setfactor(3, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(pol, iv),
        (double)987.5f,
        (double)granularity);
}
