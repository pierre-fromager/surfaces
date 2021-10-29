
#include "suite_integral.h"

static factory_ext_t factext;
static polynomial_t *p;
static interval_t iv;
static polynomial_order_t ocpt;
static polynomial_item_t cptv;
static char *result;
static const double granularity = 0.00001f;
static char gmp_buff[INTEG_FACTORY_BUF_SIZE];
static char buff_compare[INTEG_FACTORY_BUF_SIZE];

void reset_test_integral()
{
    iv = (interval_t){.l = IL_L, .h = IL_H};
    strcpy(result, "");
    strcpy(gmp_buff, "");
    strcpy(buff_compare, "");
    polynomial_destruct(p);
}

static int suite_setup(void)
{
    p = (polynomial_t *)malloc(sizeof(polynomial_t));
    iv = (interval_t){.l = IL_L, .h = IL_H};
    result = malloc(sizeof(char) * 1024 * 10);
    factext = (factory_ext_t){
        .eng = 0,
        .precision = 64};
    return 0;
}

static int suite_teardown(void)
{
    free(result);
    free(p);
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
    {test_surfaces_integral_ref_o1, "integral_ref_o1"},
    {test_surfaces_integral_trapez_o1, "integral_trapez_o1"},
    {test_surfaces_integral_midpnt_o1, "integral_midpnt_o1"},
    {test_surfaces_integral_factory_o0, "integral_factory_o0"},
    {test_surfaces_integral_factory_o1, "integral_factory_o1"},
    {test_surfaces_integral_factory_o2, "integral_factory_o2"},
    {test_surfaces_integral_factory_o3, "integral_factory_o3"},
    {test_surfaces_integral_factory_o1024, "integral_factory_o1024"},
    {test_surfaces_integral_factory_o2048, "integral_factory_o2048"},
    {test_surfaces_integral_factory_o4096, "integral_factory_o4096"},
    {test_surfaces_integral_ref_o2, "integral_ref_o2"},
    {test_surfaces_integral_ref_o3, "integral_ref_o3"},
    {test_surfaces_integral_ref_o4, "integral_ref_o4"},
    {test_surfaces_integral_ref_gmp_int_o4096, "integral_ref_gmp_int_o4096"},
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
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = 10
    polynomial_setfactor(io, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    // y = k => (-ev < k < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_reference(p, iv), (iv.h - iv.l) * cptv);
    }

    reset_test_integral();
}

void test_surfaces_integral_trapez_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = 10
    polynomial_setfactor(io, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    // y = k => (-ev < k < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_trapez(p, iv), (iv.h - iv.l) * cptv);
    }
    reset_test_integral();
}

void test_surfaces_integral_midpnt_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = 10
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_midpnt(p, iv), (iv.h - iv.l) * cptv);
    }

    reset_test_integral();
}

void test_surfaces_integral_simpson_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = ev
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_simpson(p, iv), (iv.h - iv.l) * cptv);
    }

    reset_test_integral();
}

void test_surfaces_integral_factory_riemann_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t dxi = iv.h - iv.l;
    const polynomial_item_t nbr = 2.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = ev
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    // y = x => (-ev < x < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(p, iv, nbr, riemann_left),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(p, iv, nbr, riemann_right),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(p, iv, nbr, riemann_middle_point),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(p, iv, nbr, riemann_trapezoid),
            dxi * cptv);
    }
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(io, cptv, p);
        CU_ASSERT_EQUAL(
            integral_factory_riemann(p, iv, nbr, riemann_rectangle),
            dxi * cptv);
    }

    reset_test_integral();
}

void test_surfaces_integral_ref_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x
    polynomial_setfactor(1, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), ev);
    // y = cptv * x => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_reference(p, iv), expected * cptv);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_reference(p, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_reference(p, iv), expected2xplusten);

    reset_test_integral();
}

void test_surfaces_integral_trapez_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x
    polynomial_setfactor(1, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), ev);
    // y = cptv * x => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_trapez(p, iv), expected * cptv);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_trapez(p, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_trapez(p, iv), expected2xplusten);

    reset_test_integral();
}

void test_surfaces_integral_midpnt_o1()
{
    const polynomial_order_t io = 1;
    const polynomial_item_t ev = 100.0f;
    const polynomial_item_t expected = 12.5f;
    const polynomial_item_t expectedplusten = 62.5f;
    const polynomial_item_t expected2xplusten = 75.0f;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x
    polynomial_setfactor(1, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), ev);
    // y = cptv => (-ev < cptv < ev)
    for (cptv = -ev; cptv < ev; cptv++)
    {
        polynomial_setfactor(1, cptv, p);
        CU_ASSERT_EQUAL(integral_poly_midpnt(p, iv), expected * cptv);
    }
    // y = x + 10
    polynomial_setfactor(0, 10.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1.0f);
    CU_ASSERT_EQUAL(integral_poly_midpnt(p, iv), expectedplusten);
    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2.0f);
    CU_ASSERT_EQUAL(integral_poly_midpnt(p, iv), expected2xplusten);

    reset_test_integral();
}

void test_surfaces_integral_factory_o0()
{
    const polynomial_order_t io = 0;
    const polynomial_item_t ev = 100.0f;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), io);
    // y = 100
    polynomial_setfactor(0, ev, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), ev);
    strcpy(gmp_buff, "");
    strcpy(buff_compare, "");
    snprintf(
        gmp_buff,
        sizeof(char) * INTEG_FACTORY_BUF_SIZE,
        "%Lf",
        integral_poly_midpnt(p, iv));
    integral_factory(p, iv, buff_compare, factext);
    CU_ASSERT_STRING_EQUAL(gmp_buff, buff_compare);
    reset_test_integral();
}

void test_surfaces_integral_factory_o1()
{
    const polynomial_order_t io = 1;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);

    // y = x
    polynomial_setfactor(0, 0.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "12.500000");

    // y = x + 10
    polynomial_setfactor(0, 10.0f, p);
    polynomial_setfactor(1, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 1.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "62.500000");

    // y = 2x + 10
    polynomial_setfactor(1, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 2.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "75.000000");

    reset_test_integral();
}

void test_surfaces_integral_factory_o2()
{
    const polynomial_order_t io = 2;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);

    // y = x^2
    polynomial_setfactor(0, 0.0f, p);
    polynomial_setfactor(1, 0.0f, p);
    polynomial_setfactor(2, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "41.666667");

    // y = x^2 + 10
    polynomial_setfactor(0, 10.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "91.666667");

    // y = 2x^2 + 10
    polynomial_setfactor(2, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 2.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "133.333333");

    reset_test_integral();
}

void test_surfaces_integral_factory_o3()
{
    const polynomial_order_t io = 3;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);

    // y = x^3
    polynomial_setfactor(3, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(1, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 0);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 1);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "156.250000");

    // y = x^3 + 10
    polynomial_setfactor(0, 10.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "206.250000");

    // y = 2x^2 + 10
    polynomial_setfactor(3, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 2.0f);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_STRING_EQUAL(result, "362.500000");

    reset_test_integral();
}

void test_surfaces_integral_factory_o1024()
{
    const polynomial_order_t io = 1024;
    const unsigned long int rlen = 714;
    mpz_t acc;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);

    // y = x^1024
    polynomial_ratio_t ra1024;
    polynomial_setratio(io, 1, 1, p);
    ra1024 = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(ra1024.num, 1);
    CU_ASSERT_EQUAL(ra1024.denom, 1);
    mpz_init2(acc, (mp_bitcnt_t)factext.precision);
    integral_poly_reference_gmp(acc, p, iv, (mp_bitcnt_t)factext.precision);
    strcpy(buff_compare, "");
    gmp_sprintf(buff_compare, "%Zd", acc);
    mpz_clear(acc);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_EQUAL(strlen(buff_compare), rlen);
    CU_ASSERT_EQUAL(strlen(result), rlen);
    CU_ASSERT_STRING_EQUAL(result, buff_compare);
    reset_test_integral();
}

void test_surfaces_integral_factory_o2048()
{
    const polynomial_order_t io = 2048;
    const unsigned long int rlen = 1429;
    mpz_t acc;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);

    // y = x^2048
    polynomial_ratio_t ra2048;
    polynomial_setratio(io, 1, 1, p);
    ra2048 = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(ra2048.num, 1);
    CU_ASSERT_EQUAL(ra2048.denom, 1);
    mpz_init2(acc, (mp_bitcnt_t)factext.precision);
    integral_poly_reference_gmp(acc, p, iv, (mp_bitcnt_t)factext.precision);
    strcpy(buff_compare, "");
    gmp_sprintf(buff_compare, "%Zd", acc);
    mpz_clear(acc);
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_EQUAL(strlen(buff_compare), rlen);
    CU_ASSERT_EQUAL(strlen(result), rlen);
    CU_ASSERT_STRING_EQUAL(result, buff_compare);
    reset_test_integral();
}

void test_surfaces_integral_factory_o4096()
{
    const polynomial_order_t io = 4096;
    const unsigned long int rlen = 2861;
    mpz_t acc;

    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    CU_ASSERT_EQUAL(p->order, io);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).num, 0);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getratio(ocpt, p).denom, 1);

    // y = x^4096
    polynomial_ratio_t ra4096;
    polynomial_setratio(io, 1, 1, p);
    ra4096 = polynomial_getratio(io, p);
    CU_ASSERT_EQUAL(ra4096.num, 1);
    CU_ASSERT_EQUAL(ra4096.denom, 1);
    mpz_init2(acc, (mp_bitcnt_t)factext.precision);
    integral_poly_reference_gmp(acc, p, iv, (mp_bitcnt_t)factext.precision);
    strcpy(buff_compare, "");
    gmp_sprintf(buff_compare, "%Zd", acc);
    mpz_clear(acc);
    //printf("%zu\n",strlen(buff_compare));
    strcpy(result, "");
    integral_factory(p, iv, result, factext);
    CU_ASSERT_EQUAL(strlen(buff_compare), rlen);
    CU_ASSERT_EQUAL(strlen(result), rlen);
    CU_ASSERT_STRING_EQUAL(result, buff_compare);
    reset_test_integral();
}

void test_surfaces_integral_ref_o2()
{
    const polynomial_order_t io = 2;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x²
    polynomial_setfactor(2, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)41.666667f,
        (double)granularity);
    // y = x² + 10
    polynomial_setfactor(0, 10.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)91.666667,
        (double)granularity);
    // y = 2x² + 10
    polynomial_setfactor(2, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(2, p), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)133.333333,
        (double)granularity);

    reset_test_integral();
}

void test_surfaces_integral_ref_o3()
{
    const polynomial_order_t io = 3;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x³
    polynomial_setfactor(3, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)156.25f,
        (double)granularity);
    // y = x³ + 10
    polynomial_setfactor(0, 10.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)206.25f,
        (double)granularity);
    // y = 2x³ + 10
    polynomial_setfactor(3, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)362.5f,
        (double)granularity);

    reset_test_integral();
}

void test_surfaces_integral_ref_o4()
{
    const polynomial_order_t io = 4;
    CU_ASSERT_PTR_NOT_NULL_FATAL(p);
    polynomial_construct(io, p);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getorder(ocpt, p), ocpt);
    for (ocpt = 0; ocpt < io + 1; ocpt++)
        CU_ASSERT_EQUAL(polynomial_getfactor(ocpt, p), 0);
    // y = x⁴
    polynomial_setfactor(io, 1.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(io, p), 1.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)625.0f,
        (double)granularity);
    // y = x⁴ + 10
    polynomial_setfactor(0, 10.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(0, p), 10.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)675.0f,
        (double)granularity);
    // y = 2x⁴ + 10
    polynomial_setfactor(3, 2.0f, p);
    CU_ASSERT_EQUAL(polynomial_getfactor(3, p), 2.0f);
    CU_ASSERT_DOUBLE_EQUAL(
        (double)integral_poly_reference(p, iv),
        (double)987.5f,
        (double)granularity);

    reset_test_integral();
}

void test_surfaces_integral_ref_gmp_int_o4096()
{
    const polynomial_item_t ev = 1.0f;
    const polynomial_order_t io = 4096;
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

    strcat(gmp_buff, "");
    strcat(buff_compare, "");
    mpz_init2(acc, (mp_bitcnt_t)factext.precision);

    iv.l = 1;
    iv.h = 2;
    integral_poly_reference_gmp(acc, p, iv, (mp_bitcnt_t)factext.precision);
    gmp_sprintf(gmp_buff, "%Zd", acc);
    renderer_render_bc("(2^4097)/4097", buff_compare, 0);
    CU_ASSERT_STRING_EQUAL(gmp_buff, buff_compare);

    mpz_clear(acc);

    reset_test_integral();
}
