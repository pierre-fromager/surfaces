
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
    {test_surfaces_integral_ref_o0, "integral_ref_o0"},
    {test_surfaces_integral_trapez_o0, "integral_trapez_o0"},
    {test_surfaces_integral_midpnt_o0, "integral_midpnt_o0"},
    {test_surfaces_integral_riemann_left_o0, "integral_riemann_left_o0"},
    {test_surfaces_integral_riemann_right_o0, "integral_riemann_right_o0"},
    {test_surfaces_integral_riemann_trap_o0, "integral_riemann_trap_o0"},
    {test_surfaces_integral_riemann_rect_o0, "integral_riemann_rect_o0"},
    {test_surfaces_integral_riemann_mp_o0, "integral_riemann_mp_o0"},
    {test_surfaces_integral_simpson_o0, "integral_simpson_o0"},
    {test_surfaces_integral_factory_o0, "integral_factory_o0"},
    {test_surfaces_integral_ref_o1, "integral_ref_o1"},
    {test_surfaces_integral_trapez_o1, "integral_trapez_o1"},
    {test_surfaces_integral_midpnt_o1, "integral_midpnt_o1"},
    {test_surfaces_integral_riemann_left_o1, "integral_riemann_left_o1"},
    {test_surfaces_integral_riemann_right_o1, "integral_riemann_right_o1"},
    {test_surfaces_integral_riemann_trap_o1, "integral_riemann_trap_o1"},
    {test_surfaces_integral_riemann_rect_o1, "integral_riemann_rect_o1"},
    {test_surfaces_integral_riemann_mp_o1, "integral_riemann_mp_o1"},
    {test_surfaces_integral_factory_o1, "integral_factory_o1"},
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

void test_surfaces_integral_ref_o0()
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
        CU_ASSERT_EQUAL(integral_poly_reference(pol, iv), (iv.h - iv.l) * cptv);
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

void test_surfaces_integral_riemann_left_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t nb_rect = 2.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    const polynomial_item_t ifr_left = integral_factory_riemann(
        pol,
        iv,
        nb_rect,
        riemann_left);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_left,
        (double)(5.0f * ev),
        0.00001);
}

void test_surfaces_integral_riemann_right_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t nb_rect = 2.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    const polynomial_item_t ifr_right = integral_factory_riemann(
        pol,
        iv,
        nb_rect,
        riemann_right);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_right,
        (double)(5.0f * ev),
        0.00001);
}

void test_surfaces_integral_riemann_trap_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t nb_rect = 2.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    const polynomial_item_t ifr_trap = integral_factory_riemann(
        pol,
        iv,
        nb_rect,
        riemann_trapezoid);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_trap,
        (double)(5.0f * ev),
        0.00001);
}

void test_surfaces_integral_riemann_rect_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t nb_rect = 2.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    const polynomial_item_t ifr_rect = integral_factory_riemann(
        pol,
        iv,
        nb_rect,
        riemann_rectangle);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_rect,
        (double)(5.0f * ev),
        0.00001);
}

void test_surfaces_integral_riemann_mp_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t nb_rect = 2.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), io);
    // y = ev
    polynomial_setfactor(0, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), ev);
    const polynomial_item_t ifr_mp = integral_factory_riemann(
        pol,
        iv,
        nb_rect,
        riemann_middle_point);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_mp,
        (double)(5.0f * ev),
        0.00001);
}

void test_surfaces_integral_simpson_o0()
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

void test_surfaces_integral_factory_o0()
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
    // y = 100
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

void test_surfaces_integral_riemann_left_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
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
        CU_ASSERT_DOUBLE_EQUAL(
            integral_factory_riemann(pol, iv, 1.0f, riemann_left),
            0.0f,
            0.00001);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 1.0f, riemann_left),
        (double)50.0f,
        0.00001);

    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 3.0f, riemann_left),
        (double)66.666667f,
        0.00001);
}

void test_surfaces_integral_riemann_right_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_right),
        (double)1875.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_right),
        (double)68.75f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 3.0f, riemann_right),
        (double)83.333333f,
        0.00001);
}

void test_surfaces_integral_riemann_trap_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_trapezoid),
        (double)1250.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_trapezoid),
        (double)62.5f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 3.0f, riemann_trapezoid),
        (double)75.0,
        0.00001);
}

void test_surfaces_integral_riemann_rect_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_rectangle),
        (double)625.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_rectangle),
        (double)56.25f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 3.0f, riemann_rectangle),
        (double)66.666667f,
        0.00001);
}

void test_surfaces_integral_riemann_mp_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    polynomial_order_t iocpt;
    CU_ASSERT_PTR_NOT_NULL_FATAL(pol);
    polynomial_construct(io, pol);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, pol), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, pol), 0);
    // y = x
    polynomial_setfactor(1, ev, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), ev);
    printf("%Lf\n", integral_factory_riemann(pol, iv, 2.0f, riemann_middle_point));
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_middle_point),
        (double)1250.0f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 2.0f, riemann_middle_point),
        (double)62.5f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_factory_riemann(pol, iv, 3.0f, riemann_middle_point),
        (double)75.0f,
        0.00001);
}

void test_surfaces_integral_factory_o1()
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
