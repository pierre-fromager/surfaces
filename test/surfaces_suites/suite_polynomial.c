
#include "suite_polynomial.h"

static const mp_bitcnt_t precision = 64U;
static const mpfr_prec_t precision_mpfr = 256U;
static const char *gmpfmtint = "%Zd";
static const char *gmpfrfmt = "%Rf";
static const char *__emptychar = "";
static const char *expected_dec = ".000000";
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

static void check_poly_prepare(polynomial_order_t o)
{
    polynomial_order_t iocpt;
    for (iocpt = 0; iocpt < o + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(iocpt, p), iocpt);
    for (iocpt = 0; iocpt < o + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(iocpt, p), 0);
    for (iocpt = 0; iocpt < o + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).num, 0);
    for (iocpt = 0; iocpt < o + 1; iocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(iocpt, p).denom, 1);
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
    {test_surfaces_polynomial_gmp_int, "polynomial_gmp_int"},
    {test_surfaces_polynomial_gmpfr_o0, "polynomial_gmpfr_o0"},
    {test_surfaces_polynomial_gmpfr_o64, "polynomial_gmpfr_o64"},
    {test_surfaces_polynomial_gmpfr_o128, "polynomial_gmpfr_o128"},
    {test_surfaces_polynomial_gmpfr_o256, "polynomial_gmpfr_o256"},
    {test_surfaces_polynomial_gmpfr_o512, "polynomial_gmpfr_o512"},
    {test_surfaces_polynomial_gmpfr_o1024, "polynomial_gmpfr_o1024"},
    {test_surfaces_polynomial_gmpfr_o2048, "polynomial_gmpfr_o2048"},
    {test_surfaces_polynomial_gmpfr_o4096, "polynomial_gmpfr_o4096"},
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
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);

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
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);

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
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
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
    CU_ASSERT_EQUAL(r2.num, -2);
    CU_ASSERT_EQUAL(r2.denom, 1);

    reset_test_polynomial();
}

void test_surfaces_polynomial_o3()
{
    const polynomial_item_t ev = 10.0f;
    const polynomial_order_t io = 3;
    polynomial_item_t cptv;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
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

void test_surfaces_polynomial_gmp_int()
{
    const polynomial_order_t io = 4097;

    mpz_t acc;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);

    polynomial_setratio(io, 1, 1, p);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).num, 1);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).denom, 1);
    mpz_init2(acc, precision);
    polynomial_reset(p);
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(64, 1, 1, p);
    strcpy(gmp_buff, "");
    strcpy(buff_compare, "");
    polynomial_calc_gmp_int(acc, 2.0f, p, precision);
    gmp_sprintf(gmp_buff, gmpfmtint, acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, "18446744073709551640");
    renderer_render_bc("(-2^3)+(2^4)+(2^64)", buff_compare, 0);
    CU_ASSERT_STRING_EQUAL(buff_compare, "18446744073709551624");

    mpz_clear(acc);
    reset_test_polynomial();
}

void test_surfaces_polynomial_gmpfr_o0()
{
    const polynomial_order_t io = 0;
    const char *expected = "1.333333";

    mpfr_t acc;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    // y = 4/3
    polynomial_setratio(io, 4, 3, p);

    CU_ASSERT_EQUAL(polynomial_getratio(io, p).num, 4);
    CU_ASSERT_EQUAL(polynomial_getratio(io, p).denom, 3);
    mpfr_init2(acc, precision_mpfr);
    strcpy(gmp_buff, "");
    mpfr_set_d(acc, 0.0f, MPFR_RNDN);
    polynomial_calc_gmp_mpfr(acc, 0.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, expected);
    strcpy(gmp_buff, "");
    mpfr_set_d(acc, 0.0f, MPFR_RNDN);
    polynomial_calc_gmp_mpfr(acc, 1.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, expected);
    mpfr_clear(acc);
    reset_test_polynomial();
}

void test_surfaces_polynomial_gmpfr_o64()
{
    const polynomial_order_t io = 64;
    mpfr_t acc;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr);

    // y = -x^3 + x^4 + x^64
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(64, 1, 1, p);

    strcpy(gmp_buff, "");
    strcpy(buff_compare, "");
    polynomial_calc_gmp_mpfr(acc, 2.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    CU_ASSERT_STRING_EQUAL(gmp_buff, "18446744073709551624"
                                     ".000000");
    renderer_render_bc("(-2^3)+(2^4)+(2^64)", buff_compare, 6);
    CU_ASSERT_STRING_EQUAL(buff_compare, "18446744073709551624");
    mpfr_clear(acc);
    reset_test_polynomial();
}

void test_surfaces_polynomial_gmpfr_o128()
{
    const polynomial_order_t io = 128;
    mpfr_t acc;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr);

    // y = -x^3 + x^4 + x^128
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(128, 1, 1, p);
    strcpy(gmp_buff, "");
    strcpy(buff_compare, "");
    polynomial_calc_gmp_mpfr(acc, 2.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        "340282366920938463463374607431768211464"
        ".000000");
    renderer_render_bc("(-2^3)+(2^4)+(2^128)", buff_compare, 6);
    CU_ASSERT_STRING_EQUAL(buff_compare, "340282366920938463463374607431768211464");
    mpfr_clear(acc);
    reset_test_polynomial();
}

void test_surfaces_polynomial_gmpfr_o256()
{
    const polynomial_order_t io = 256;
    mpfr_t acc;
    const char *expected_int = "11579208923731619542357098"
                               "50086879078532699846656405"
                               "64039457584007913129639944";
    char *expected;
    expected = malloc(sizeof(char) * 1024);
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr);

    // y = -x^3 + x^4 + x^256
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(io, 1, 1, p);

    strcpy(gmp_buff, __emptychar);
    strcpy(buff_compare, __emptychar);
    polynomial_calc_gmp_mpfr(acc, 2.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    strcpy(expected, __emptychar);
    strcat(expected, expected_int);
    strcat(expected, expected_dec);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        expected);
    renderer_render_bc("(-2^3)+(2^4)+(2^256)", buff_compare, 6);
    CU_ASSERT_STRING_EQUAL(
        buff_compare,
        expected_int);
    mpfr_clear(acc);
    reset_test_polynomial();
    free(expected);
}

void test_surfaces_polynomial_gmpfr_o512()
{
    const polynomial_order_t io = 512;
    mpfr_t acc;
    const char *expected_int = 
        "1340780792994259709957"
        "4024998205846127479365"
        "8205923933777235614437"
        "2176403007354697680187"
        "4298166903427690031858"
        "1864860508537538828119"
        "4656994643364900608410"
        "4";
    char *expected;
    expected = malloc(sizeof(char) * 1024);
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr * 2);

    // y = -x^3 + x^4 + x^512
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(io, 1, 1, p);

    strcpy(gmp_buff, __emptychar);
    strcpy(buff_compare, __emptychar);
    polynomial_calc_gmp_mpfr(acc, 2.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    strcpy(expected, __emptychar);
    strcat(expected, expected_int);
    strcat(expected, expected_dec);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        expected);
    renderer_render_bc("(-2^3)+(2^4)+(2^512)", buff_compare, 6);
    CU_ASSERT_STRING_EQUAL(
        buff_compare,
        expected_int);
    mpfr_clear(acc);
    reset_test_polynomial();
    free(expected);
}

void test_surfaces_polynomial_gmpfr_o1024()
{
    const polynomial_order_t io = 1024;
    mpfr_t acc;
    const char *expected_int = 
        "17976931348623159077293"
        "05190789024733617976978"
        "94230657273430081157732"
        "67580550096313270847732"
        "24075360211201138798713"
        "93357658789768814416622"
        "49284743063947412437776"
        "78934248654852763022196"
        "01246094119453082952085"
        "00576883815068234246288"
        "14739131105408272371633"
        "50510684586298239947245"
        "93847971630483535632962"
        "4224137224";
    char *expected;
    expected = malloc(sizeof(char) * 1024);
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr * 4);

    // y = -x^3 + x^4 + x^1024
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(io, 1, 1, p);

    strcpy(gmp_buff, __emptychar);
    strcpy(buff_compare, __emptychar);
    polynomial_calc_gmp_mpfr(acc, 2.0f, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    strcpy(expected, __emptychar);
    strcat(expected, expected_int);
    strcat(expected, expected_dec);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        expected);
    renderer_render_bc("(-2^3)+(2^4)+(2^1024)", buff_compare, 64);
    CU_ASSERT_STRING_EQUAL(
        buff_compare,
        expected_int);
    mpfr_clear(acc);
    reset_test_polynomial();
    free(expected);
}

void test_surfaces_polynomial_gmpfr_o2048()
{
    const polynomial_order_t io = 2048;
    const polynomial_item_t xc = 2.0f;
    const char *eqc = "(-2^3)+(2^4)+(2^2048)";    
    const char *expected_int = 
        "3231700607131100730071487668866995196044410266971548403"
        "2130345427524655138867890893197201411522913463688717960"
        "9218980194941195591504909210950881523864482831206308773"
        "6730099609175019775038965210679605763838406756827679221"
        "8642619756161838094338476170470581645852036305042887575"
        "8915410658086075523991239303855219143333896683424206849"
        "7478656456949485617603532632205807780565933102619270846"
        "0314150258592864177116725943603718461857357598351152301"
        "6459044036976132332872312271256847108202097251571017269"
        "3132346967854258065669793504599726835299863821552516638"
        "9437335543602135433229604645318478604952148193555853611"
        "059596230664";
    mpfr_t acc;    
    char *expected;
    expected = malloc(sizeof(char) * 1024);
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr * 8);

    // y = -x^3 + x^4 + x^2048
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(io, 1, 1, p);

    strcpy(gmp_buff, __emptychar);
    strcpy(buff_compare, __emptychar);
    polynomial_calc_gmp_mpfr(acc, xc, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    strcpy(expected, __emptychar);
    strcat(expected, expected_int);
    strcat(expected, expected_dec);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        expected);
    renderer_render_bc(eqc, buff_compare, 64);
    CU_ASSERT_STRING_EQUAL(
        buff_compare,
        expected_int);
    mpfr_clear(acc);
    reset_test_polynomial();
    free(expected);
}

void test_surfaces_polynomial_gmpfr_o4096()
{
    const polynomial_order_t io = 4096;
    const polynomial_item_t xc = 2.0f;
    const char *eqc = "(-2^3)+(2^4)+(2^4096)";    
    mpfr_t acc;
    const char *expected_int = 
        "10443888814131525066917527107166243825799642490473837803842334832839539079715"
        "57456848826811934997558340890106714439262837987573438185793607263236087851365"
        "27794595697654370999834036159013438371831442807001185594622637631883939771274"
        "56723346843445866174968079087058037040712840487401186091144679777835980290066"
        "86938976881787785946905630190260940599579453432823469303026696443059025015972"
        "39986771421554169383555988529148631823791443449673408781187263949647510018904"
        "13490084170616750936683338505510329720882695507699836163694119330152137968258"
        "37188091833656751221318492846368125550225998300412344784862595674492194617023"
        "80650591324561082573183538008760862210283427019769820231316901767800667519548"
        "50799216364193702853751247840149071591354599827905133996115517942711068311340"
        "90584272884279791554849782954323534517065223269061394905987693002122963395687"
        "78287894844061600741294567491982305057164237715481632138063104590291613692670"
        "83428564407304478999719017814657634732238502672530598997959960907994692017746"
        "24817718449867455659250178329070473119433165550807568221846571746373296884912"
        "81952031745700244092661691087414838507841192980452298185733897764810312608590"
        "30013024134671897266732164915111316029207817380334360902438047083404031541903"
        "44";
    char *expected;
    expected = malloc(sizeof(char) * 1024);
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    check_poly_prepare(io);
    mpfr_init2(acc, precision_mpfr * 16);

    // y = -x^3 + x^4 + x^4096
    polynomial_setratio(3, -1, 1, p);
    polynomial_setratio(4, 1, 1, p);
    polynomial_setratio(io, 1, 1, p);

    strcpy(gmp_buff, __emptychar);
    strcpy(buff_compare, __emptychar);
    polynomial_calc_gmp_mpfr(acc, xc, p, precision_mpfr);
    mpfr_sprintf(gmp_buff, gmpfrfmt, acc);
    strcpy(expected, __emptychar);
    strcat(expected, expected_int);
    strcat(expected, expected_dec);
    CU_ASSERT_STRING_EQUAL(
        gmp_buff,
        expected);
    renderer_render_bc(eqc, buff_compare, 64);
    CU_ASSERT_STRING_EQUAL(
        buff_compare,
        expected_int);
    mpfr_clear(acc);
    reset_test_polynomial();
    free(expected);
}
