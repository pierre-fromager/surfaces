
#include "suite_roots.h"

static const double granularity = 0.000001f;
static polynomial_order_t maxo = 5 + 1;
static polynomial_t *p;
static polynomial_item_t *r;
//static root_complex_t croots;

void reset_test_roots()
{
    polynomial_order_t cpto;
    for (cpto = 0; cpto < maxo; cpto++)
        *(r + cpto) = 0.0f;
    polynomial_destruct(p);
    //croots = (root_complex_t){.real = 0.0f, .imag = 0.0f};
}

static int suite_setup(void)
{
    p = (polynomial_t *)malloc(sizeof(polynomial_t));
    r = (polynomial_item_t *)malloc(sizeof(polynomial_item_t) * maxo);
    return 0;
}

static int suite_teardown(void)
{
    free(r);
    free(p);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_roots_factory_o0, "roots_factory_o0"},
    {test_surfaces_roots_factory_o1, "roots_factory_o1"},
    {test_surfaces_roots_factory_o2, "roots_factory_o2"},
    {test_surfaces_roots_factory_o3, "roots_factory_o3"},
    {test_surfaces_roots_factory_o4, "roots_factory_o4"},
    {0, 0},
};

void test_surfaces_roots_add_suite()
{
    const char *suite_name = "roots";
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

static void poly_check(polynomial_order_t o)
{
    polynomial_order_t ocpt;
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < o + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);
}

void test_surfaces_roots_factory_o0()
{
    const polynomial_order_t io = 0;
    polynomial_order_t res;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    poly_check(io);
    // y = 0
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    // y = 10
    polynomial_setfactor(0, 10.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    // y = -10
    polynomial_setfactor(0, -10.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    reset_test_roots();
}

void test_surfaces_roots_factory_o1()
{
    const polynomial_order_t io = 1;
    polynomial_order_t res;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    poly_check(io);
    // y = 0x + 0
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), 0);
    // y = 0x + 10
    polynomial_setfactor(0, 10.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), 0);
    // y = x + 10
    polynomial_setfactor(1, 1.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), -10);
    // y = 5x + 10
    polynomial_setfactor(1, 5.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), -2);
    // y = 1/2x + 10
    polynomial_setfactor(1, 0.5f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), -20);
    // y = -1/2x + 10
    polynomial_setfactor(1, -0.5f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), 20);
    // y = -1/2x - 10
    polynomial_setfactor(0, -10.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), -20);
    reset_test_roots();
}

void test_surfaces_roots_factory_o2()
{
    const polynomial_order_t io = 2;
    polynomial_order_t res;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    poly_check(io);
    // y = 0x^2 + 0x + 0
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 0);
    // y = x^2
    polynomial_setfactor(2, 1.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 1);
    CU_ASSERT_EQUAL(*(r + 0), 0);
    // y = x^2 + x
    polynomial_setfactor(1, 1.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 2);
    CU_ASSERT_EQUAL(*(r + 0), -1);
    CU_ASSERT_EQUAL(*(r + 1), 0);
    // y = x^2 + x + 10
    polynomial_setfactor(0, 10.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 0);
    // y = 2x^2 + x
    polynomial_setfactor(0, 0.0f, p);
    polynomial_setfactor(2, 2.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_EQUAL(*(r + 0), -0.5f);
    CU_ASSERT_EQUAL(*(r + 1), 0);
    // y = x^2 + x - 10
    polynomial_setfactor(0, -10.0f, p);
    polynomial_setfactor(2, 1.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_DOUBLE_EQUAL(*(r + 0), -3.701562, granularity);
    CU_ASSERT_DOUBLE_EQUAL(*(r + 1), 2.701562, granularity);
    // y = 2x^2 + x - 10
    polynomial_setfactor(2, 2.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    CU_ASSERT_DOUBLE_EQUAL(*(r + 0), -2.5, granularity);
    CU_ASSERT_DOUBLE_EQUAL(*(r + 1), 2, granularity);

    reset_test_roots();
}

void test_surfaces_roots_factory_o3()
{
    const polynomial_order_t io = 3;
    polynomial_order_t res;
    unsigned short cptr;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    poly_check(io);
    // y = 0x^3 + 0x^2 + 0x + 0
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 0);
    for (cptr = 0; cptr < io; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            0.0f,
            granularity);
    // y = x^3 + x^2 + x
    polynomial_reset(p);
    polynomial_setfactor(3, 1.0f, p);
    polynomial_setfactor(2, 1.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    polynomial_setfactor(0, 0.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 1);
    CU_ASSERT_EQUAL(*(r + 0), 0);
    // y = 10x^3 -10x^2 + 10x
    polynomial_reset(p);
    polynomial_setfactor(3, 10.0f, p);
    polynomial_setfactor(2, 10.0f, p);
    polynomial_setfactor(1, 10.0f, p);
    polynomial_setfactor(0, 0.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 1);
    CU_ASSERT_EQUAL(*(r + 0), 0);
    // y = x^3 -15x -4
    polynomial_reset(p);
    polynomial_setfactor(3, 1.0f, p);
    polynomial_setfactor(1, -15.0f, p);
    polynomial_setfactor(0, -4.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    const double sr0[3] = {-3.732051f, -0.267949f, 4.0f};
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            sr0[cptr],
            granularity);
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            polynomial_calc(*(r + cptr), p),
            0.0f,
            granularity);
    // y = 2x^3 + x^2 - 15x - 4
    polynomial_reset(p);
    polynomial_setfactor(3, 2.0f, p);
    polynomial_setfactor(2, 1.0f, p);
    polynomial_setfactor(1, -15.0f, p);
    polynomial_setfactor(0, -4.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, io);
    const double sr1[3] = {-2.870247f, -0.264470f, 2.634717f};
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            sr1[cptr],
            granularity);
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            polynomial_calc(*(r + cptr), p),
            0.0f,
            granularity);
    reset_test_roots();
}

void test_surfaces_roots_factory_o4()
{
    const polynomial_order_t io = 4;
    polynomial_order_t res;
    unsigned short cptr;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    poly_check(io);
    // y = 0x^4 + 0x^3 + 0x^2 + 0x + 0
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 0);
    for (cptr = 0; cptr < io; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            0.0f,
            granularity);
    // y = 3x^4 + 6x^3 - 123x^2 -126x + 1080
    polynomial_reset(p);
    polynomial_setfactor(4, 3.0f, p);
    polynomial_setfactor(3, 6.0f, p);
    polynomial_setfactor(2, -123.0f, p);
    polynomial_setfactor(1, -126.0f, p);
    polynomial_setfactor(0, 1080.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 4);
    const double sr0[4] = {-6.0f, -4.0f, 3.0f, 5.0f};
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            sr0[cptr],
            granularity);
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(polynomial_calc(*(r + cptr), p), 0, granularity);
    polynomial_reset(p);

    // y = -20x^4 + 5x^3 + 17x^2 - 29x + 87
    polynomial_reset(p);
    polynomial_setfactor(4, -20.0f, p);
    polynomial_setfactor(3, 5.0f, p);
    polynomial_setfactor(2, 17.0f, p);
    polynomial_setfactor(1, -29.0f, p);
    polynomial_setfactor(0, 87.0f, p);
    res = roots_factory(p, r);
    CU_ASSERT_EQUAL(res, 2);
    const double sr1[4] = {-1.682004f, 1.487583};
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            *(r + cptr),
            sr1[cptr],
            granularity);
    for (cptr = 0; cptr < res; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(polynomial_calc(*(r + cptr), p), 0, granularity);
    polynomial_reset(p);

    reset_test_roots();
}