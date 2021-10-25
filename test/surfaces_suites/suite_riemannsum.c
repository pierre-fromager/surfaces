
#include "suite_riemannsum.h"

static polynomial_t *pol;
static interval_t iv;

void reset_test_riemannsum()
{
    iv = (interval_t){.l = IL_L, .h = IL_H};
    polynomial_destruct(pol);
}

static int suite_setup(void)
{
    pol = (polynomial_t *)malloc(sizeof(polynomial_t));
    iv = (interval_t){.l = IL_L, .h = IL_H};
    return 0;
}

static int suite_teardown(void)
{
    free(pol);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_riemannsum_left_o0, "riemann_sum_left_o0"},
    {test_surfaces_riemannsum_right_o0, "riemann_sum_right_o0"},
    {test_surfaces_riemannsum_trap_o0, "riemann_sum_trap_o0"},
    {test_surfaces_riemannsum_rect_o0, "riemann_sum_rect_o0"},
    {test_surfaces_riemannsum_mp_o0, "riemann_sum_mp_o0"},
    {test_surfaces_riemannsum_left_o1, "riemann_sum_left_o1"},
    {test_surfaces_riemannsum_right_o1, "riemann_sum_right_o1"},
    {test_surfaces_riemannsum_trap_o1, "riemann_sum_trap_o1"},
    {test_surfaces_riemannsum_rect_o1, "riemann_sum_rect_o1"},
    {test_surfaces_riemannsum_mp_o1, "riemann_sum_mp_o1"},
    {0, 0},
};

void test_surfaces_riemannsum_add_suite()
{
    const char *suite_name = "riemannsum";
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

void test_surfaces_riemannsum_left_o0()
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
    const polynomial_item_t ifr_left = riemann_sum_left(
        pol,
        iv,
        nb_rect);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_left,
        (double)(5.0f * ev),
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_right_o0()
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
    const polynomial_item_t ifr_right = riemann_sum_right(
        pol,
        iv,
        nb_rect);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_right,
        (double)(5.0f * ev),
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_trap_o0()
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
    const polynomial_item_t ifr_trap = riemann_sum_trap(
        pol,
        iv,
        nb_rect);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_trap,
        (double)(5.0f * ev),
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_rect_o0()
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
    const polynomial_item_t ifr_rect = riemann_sum_rect(
        pol,
        iv,
        nb_rect);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_rect,
        (double)(5.0f * ev),
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_mp_o0()
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
    const polynomial_item_t ifr_mp = riemann_sum_mp(
        pol,
        iv,
        nb_rect);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)ifr_mp,
        (double)(5.0f * ev),
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_left_o1()
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
            riemann_sum_left(pol, iv, 1.0f),
            0.0f,
            0.00001);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_left(pol, iv, 1.0f),
        (double)50.0f,
        0.00001);

    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_left(pol, iv, 3.0f),
        (double)66.666667f,
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_right_o1()
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
        (double)riemann_sum_right(pol, iv, 2.0f),
        (double)1875.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_right(pol, iv, 2.0f),
        (double)68.75f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_right(pol, iv, 3.0f),
        (double)83.333333f,
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_trap_o1()
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
        (double)riemann_sum_trap(pol, iv, 2.0f),
        (double)1250.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_trap(pol, iv, 2.0f),
        (double)62.5f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_trap(pol, iv, 3.0f),
        (double)75.0,
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_rect_o1()
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
        (double)riemann_sum_rect(pol, iv, 2.0f),
        (double)625.00f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_rect(pol, iv, 2.0f),
        (double)56.25f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_rect(pol, iv, 3.0f),
        (double)66.666667f,
        0.00001);

    reset_test_riemannsum();
}

void test_surfaces_riemannsum_mp_o1()
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
        (double)riemann_sum_mp(pol, iv, 2.0f),
        (double)1250.0f,
        0.00001);
    // y = x + 10
    polynomial_setfactor(0, 10.0f, pol);
    polynomial_setfactor(1, 1.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, pol), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_mp(pol, iv, 2.0f),
        (double)62.5f,
        0.00001);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, pol);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, pol), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)riemann_sum_mp(pol, iv, 3.0f),
        (double)75.0f,
        0.00001);

    reset_test_riemannsum();
}