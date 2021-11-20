
#include "suite_intersect.h"

static const polynomial_order_t o0 = 0;
static const polynomial_order_t o1 = 1;
static const polynomial_order_t o2 = 2;
static const polynomial_order_t o12 = 12;
static const polynomial_order_t o14 = 14;
static const double granularity = 0.000001f;
static polynomial_t *p1, *p2;
static coord_t *coords;
static interval_t ivl;

void reset_test_intersect()
{
    ivl = (interval_t){.l = -10, .h = 10};
    polynomial_destruct(p1);
    polynomial_destruct(p2);
}

static int suite_setup(void)
{
    p1 = (polynomial_t *)malloc(sizeof(polynomial_t));
    p2 = (polynomial_t *)malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    free(p1);
    free(p2);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_poly_intersect_o0, "intersect_o0"},
    {test_surfaces_poly_intersect_o1, "intersect_o1"},
    {test_surfaces_poly_intersect_o1_nosol, "intersect_o1_nosol"},
    {test_surfaces_poly_intersect_o2, "intersect_o2"},
    {test_surfaces_poly_intersect_o14, "intersect_o14"},
    {0, 0},
};

void test_surfaces_intersect_add_suite()
{
    const char *suite_name = "intersect";
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

void test_surfaces_poly_intersect_o0()
{
    polynomial_order_t nbres, ho;
    // p1 = 3
    polynomial_construct(o0, p1);
    polynomial_setfactor(o0, 3.0f, p1);
    CU_ASSERT_EQUAL(p1->order, o0);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p1), 3);
    // p2 = 2
    polynomial_construct(o0, p2);
    polynomial_setfactor(o0, 2.0f, p2);
    CU_ASSERT_EQUAL(p2->order, o0);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p2), 2);
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    nbres = poly_intersect(p1, p2, ivl, coords);
    CU_ASSERT_EQUAL(nbres, 0);
    free(coords);
    reset_test_intersect();
}

void test_surfaces_poly_intersect_o1()
{
    polynomial_order_t nbres, ho;
    // p1 = 3x
    polynomial_construct(o1, p1);
    polynomial_setfactor(o1, 3.0f, p1);
    CU_ASSERT_EQUAL(p1->order, o1);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p1), 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p1), 0);
    // p2 = 2x
    polynomial_construct(o1, p2);
    polynomial_setfactor(o1, 2.0f, p2);
    CU_ASSERT_EQUAL(p2->order, o1);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p2), 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p2), 0);
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    nbres = poly_intersect(p1, p2, ivl, coords);
    CU_ASSERT_EQUAL(nbres, 1);
    CU_ASSERT_DOUBLE_EQUAL((*(coords + 0)).x, 0.0, granularity);
    CU_ASSERT_DOUBLE_EQUAL((*(coords + 0)).y, 0.0, granularity);
    free(coords);
    reset_test_intersect();
}

void test_surfaces_poly_intersect_o1_nosol()
{
    polynomial_order_t nbres, ho;
    // p1 = 2x-1
    polynomial_construct(o1, p1);
    polynomial_setfactor(o1, 2.0f, p1);
    polynomial_setfactor(o0, -1.0f, p1);
    CU_ASSERT_EQUAL(p1->order, o1);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p1), 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p1), -1);
    // p2 = 2x
    polynomial_construct(o1, p2);
    polynomial_setfactor(o1, 2.0f, p2);
    polynomial_setfactor(o0, 0.0f, p2);
    CU_ASSERT_EQUAL(p2->order, o1);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p2), 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p2), 0);
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    nbres = poly_intersect(p1, p2, ivl, coords);
    CU_ASSERT_EQUAL(nbres, 0);
    free(coords);
    reset_test_intersect();
}

void test_surfaces_poly_intersect_o2()
{
    polynomial_order_t nbres, ho;
    unsigned short cptr;
    // p1 = 8x^2+2x-1
    polynomial_construct(o2, p1);
    polynomial_setfactor(o2, 8.0f, p1);
    polynomial_setfactor(o1, 2.0f, p1);
    polynomial_setfactor(o0, -1.0f, p1);
    CU_ASSERT_EQUAL(p1->order, o2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o2, p1), 8);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p1), 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p1), -1);
    // p2 = 5x^2+x
    polynomial_construct(o2, p2);
    polynomial_setfactor(o2, 5.0f, p2);
    polynomial_setfactor(o1, 1.0f, p2);
    polynomial_setfactor(o0, 0.0f, p2);
    CU_ASSERT_EQUAL(p2->order, o2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o2, p2), 5);
    CU_ASSERT_EQUAL(polynomial_getfactor(o1, p2), 1);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p2), 0);
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    nbres = poly_intersect(p1, p2, ivl, coords);
    CU_ASSERT_EQUAL(nbres, 2);
    const coord_t sr0[2] = {
        {.x = -0.767592, .y = 2.178395},
        {.x = 0.434259, .y = 1.377161}};
    for (cptr = 0; cptr < nbres; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            (double)(*(coords + cptr)).x,
            (double)sr0[cptr].x,
            granularity);
    free(coords);
    reset_test_intersect();
}

void test_surfaces_poly_intersect_o14()
{
    polynomial_order_t nbres, ho;
    unsigned short cptr;
    // p1 = 2x^14-100
    polynomial_construct(o14, p1);
    polynomial_setfactor(o14, 2.0f, p1);
    polynomial_setfactor(o0, -100.0f, p1);
    CU_ASSERT_EQUAL(p1->order, o14);
    CU_ASSERT_EQUAL(polynomial_getfactor(o14, p1), 2);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p1), -100);
    // p2 = 3x^12+10
    polynomial_construct(o12, p2);
    polynomial_setfactor(12, 3.0f, p2);
    polynomial_setfactor(o0, 10.0f, p2);
    CU_ASSERT_EQUAL(p2->order, o12);
    CU_ASSERT_EQUAL(polynomial_getfactor(o12, p2), 3);
    CU_ASSERT_EQUAL(polynomial_getfactor(o0, p2), 10);
    ho = (p1->order > p2->order) ? p1->order : p2->order;
    CU_ASSERT_EQUAL(ho, o14);
    coords = (coord_t *)malloc(sizeof(coord_t) * (ho + 1));
    nbres = poly_intersect(p1, p2, ivl, coords);
    // p.inter => 2x^14-3x^12-110
    CU_ASSERT_EQUAL(nbres, 2);
    const coord_t sr0[2] = {
        {.x = -1.454238, .y = 278.377029},
        {.x = 1.454238, .y = 278.377029}};
    for (cptr = 0; cptr < nbres; cptr++)
        CU_ASSERT_DOUBLE_EQUAL(
            (double)(*(coords + cptr)).x,
            (double)sr0[cptr].x,
            granularity);
    free(coords);
    reset_test_intersect();
}
