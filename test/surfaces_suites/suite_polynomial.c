
#include "suite_polynomial.h"

static polynomial_t *p;
static char gmp_buff[TEST_SURFACE_POLY_CHAR_BUFF_LEN];
static char buff_compare[TEST_SURFACE_POLY_CHAR_BUFF_LEN];

void reset_test_polynomial()
{
    polynomial_destruct(p);
}

static int suite_setup(void)
{
    p = (polynomial_t *)malloc(sizeof(polynomial_t));
    return 0;
}

static int suite_teardown(void)
{
    free(p);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_polynomial_reset, "polynomial_reset"},
    {test_surfaces_polynomial_addratio, "polynomial_addratio"},
    {test_surfaces_polynomial_o0, "polynomial_o0"},
    {test_surfaces_polynomial_o1, "polynomial_o1"},
    {test_surfaces_polynomial_o2, "polynomial_o2"},
    {test_surfaces_polynomial_o3, "polynomial_o3"},
    {test_surfaces_polynomial_o4097, "polynomial_o4097"},
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

void test_surfaces_polynomial_reset()
{
    polynomial_order_t io;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    io = 0;
    polynomial_construct(io, p);
    polynomial_setfactor(io, 1.0f, p);
    polynomial_setratio(io, 1, 1, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, p), 1);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).denom, 1);
    polynomial_reset(p);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, p), 0);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).num, 0);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).denom, 1);

    reset_test_polynomial();
}

void test_surfaces_polynomial_addratio()
{
    polynomial_order_t io;
    polynomial_ratio_t ar, r;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    io = 0;
    polynomial_construct(io, p);

    // 0/1 + 0/1 = 0/1
    ar = (polynomial_ratio_t){.num = 0, .denom = 1};
    polynomial_addratio(io, ar, p);
    r = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);
    polynomial_reset(p);

    // 0/1 + 1/2 = 1/2
    ar = (polynomial_ratio_t){.num = 1, .denom = 2};
    polynomial_addratio(io, ar, p);
    r = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r.num, 1);
    CU_ASSERT_EQUAL(r.denom, 2);
    polynomial_reset(p);

    // 1/3 - 1/3 = 0/1
    ar = (polynomial_ratio_t){.num = 1, .denom = 3};
    polynomial_addratio(io, ar, p);
    ar.num = -1;
    polynomial_addratio(io, ar, p);
    r = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);
    polynomial_reset(p);

    // 1/3 + 2/3 = 1/1
    ar = (polynomial_ratio_t){.num = 1, .denom = 3};
    polynomial_addratio(io, ar, p);
    ar.num = 2;
    polynomial_addratio(io, ar, p);
    r = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r.num, 1);
    CU_ASSERT_EQUAL(r.denom, 1);
    polynomial_reset(p);

    reset_test_polynomial();
}

void test_surfaces_polynomial_o0()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 0;
    polynomial_ratio_t pr, pracc;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
    // y = 0
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);

    // factor
    // y = 10
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), ev);

    // y = 4/3
    polynomial_setfactor(0, (polynomial_item_t)4 / 3, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), (polynomial_item_t)4 / 3);
    polynomial_reset(p);

    // add ratio
    // y = 4/3
    pracc = (polynomial_ratio_t){.num = 4, .denom = 3};
    polynomial_addratio(io, pracc, p);
    pr = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(pr.num, 4);
    CU_ASSERT_EQUAL(pr.denom, 3);
    polynomial_reset(p);

    // y = 4/3 - 4/3 = 0
    pracc = (polynomial_ratio_t){.num = 4, .denom = 3};
    polynomial_addratio(io, pracc, p);
    pracc.num = -4;
    polynomial_addratio(io, pracc, p);
    pr = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(pr.num, 0);
    CU_ASSERT_EQUAL(pr.denom, 1);
    polynomial_reset(p);

    // y = 1/3 + 2/3 = 1
    pracc = (polynomial_ratio_t){.num = 1, .denom = 3};
    polynomial_addratio(io, pracc, p);
    pracc.num = 2;
    polynomial_addratio(io, pracc, p);
    pr = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(pr.num, 1);
    CU_ASSERT_EQUAL(pr.denom, 1);
    polynomial_reset(p);

    // y = 1/3 - 1/3 = 0
    pracc = (polynomial_ratio_t){.num = 1, .denom = 3};
    polynomial_addratio(io, pracc, p);
    pracc.num = -1;
    polynomial_addratio(io, pracc, p);
    pr = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(pr.num, 0);
    CU_ASSERT_EQUAL(pr.denom, 1);
    polynomial_reset(p);

    reset_test_polynomial();
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
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
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

    polynomial_setratio(0, 5, 1, p);
    polynomial_setratio(1, -2, 1, p);
    const polynomial_ratio_t r0 = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(r0.num, 5);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r1.num, -2);
    CU_ASSERT_EQUAL(r1.denom, 1);

    reset_test_polynomial();
}

void test_surfaces_polynomial_o2()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 2;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(sizeof(p->factors), 8);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);
    // y = x²
    polynomial_setfactor(2, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv);
    // y = x² + 1
    polynomial_setfactor(0, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv + 1);
    // y = x² + 5
    polynomial_setfactor(0, 5.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 5);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv + 5);
    // y = 2x² + 5
    polynomial_setfactor(2, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), 2 * cptv * cptv + 5);
    // y = -2x² + 5
    polynomial_setfactor(2, -2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), -2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), -2 * cptv * cptv + 5);
    // y = -2x² + x + 5
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), -2 * cptv * cptv + cptv + 5);

    polynomial_setratio(0, 5, 1, p);
    polynomial_setratio(1, 1, 1, p);
    polynomial_setratio(2, -2, 1, p);
    const polynomial_ratio_t r0 = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(r0.num, 5);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, p);
    CU_ASSERT_EQUAL(r1.num, 1);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(io, p);
    //printf("r1 %d %d \n",r1.num,r1.denom);
    CU_ASSERT_EQUAL(r2.num, -2);
    CU_ASSERT_EQUAL(r2.denom, 1);

    reset_test_polynomial();
}

void test_surfaces_polynomial_o3()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 3;
    polynomial_order_t iocpt;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(sizeof(p->factors), 8);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);
    // y = x³
    polynomial_setfactor(3, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv * cptv);
    // y = x³ + 1
    polynomial_setfactor(0, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv * cptv + 1);
    // y = x³ + 5
    polynomial_setfactor(0, 5.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 5);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), cptv * cptv * cptv + 5);
    // y = 2x³ + 5
    polynomial_setfactor(3, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), 2 * cptv * cptv * cptv + 5);
    // y = -2x³ + 5
    polynomial_setfactor(3, -2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), -2);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(polynomial_calc(cptv, p), -2 * cptv * cptv * cptv + 5);
    // y = -2x³ + x² + x + 5
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    polynomial_setfactor(2, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    for (cptv = -ev; cptv < ev; cptv++)
        CU_ASSERT_EQUAL(
            polynomial_calc(cptv, p),
            (-2 * cptv * cptv * cptv) + (cptv * cptv) + cptv + 5);

    polynomial_setratio(0, 5, 1, p);
    polynomial_setratio(1, 1, 1, p);
    polynomial_setratio(2, 0, 1, p);
    polynomial_setratio(3, -2, 1, p);
    const polynomial_ratio_t r0 = polynomial_getratio(0, p);
    CU_ASSERT_EQUAL(r0.num, 5);
    CU_ASSERT_EQUAL(r0.denom, 1);
    const polynomial_ratio_t r1 = polynomial_getratio(1, p);
    CU_ASSERT_EQUAL(r1.num, 1);
    CU_ASSERT_EQUAL(r1.denom, 1);
    const polynomial_ratio_t r2 = polynomial_getratio(2, p);
    CU_ASSERT_EQUAL(r2.num, 0);
    CU_ASSERT_EQUAL(r2.denom, 1);
    const polynomial_ratio_t r3 = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(r3.num, -2);
    CU_ASSERT_EQUAL(r3.denom, 1);

    reset_test_polynomial();
}

void test_surfaces_polynomial_o4097()
{
    const polynomial_item_t ev = 1.0f;
    const polynomial_order_t io = 4097;
    const mp_bitcnt_t precision = 64;
    mpz_t acc;
    polynomial_order_t iocpt;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < io + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
    CU_ASSERT_EQUAL(polynomial_calc(ev, p), 0);

    polynomial_setratio(io, 1, 1, p);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).denom, 1);

    mpz_init2(acc, precision);

    polynomial_calc_gmp_int(acc, 0.0f, p, precision);
    gmp_sprintf(gmp_buff, "%Zd", acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, "0");

    polynomial_calc_gmp_int(acc, 1.0f, p, precision);
    gmp_sprintf(gmp_buff, "%Zd", acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, "1");

    polynomial_calc_gmp_int(acc, 2.0f, p, precision);
    mpz_sub_ui(acc,acc, (unsigned long)1);
    gmp_sprintf(gmp_buff, "%Zd", acc);
    renderer_render_bc("2^4097", buff_compare, 0);
    CU_ASSERT_STRING_EQUAL(gmp_buff, buff_compare);

    mpz_clear(acc);

    reset_test_polynomial();
}
