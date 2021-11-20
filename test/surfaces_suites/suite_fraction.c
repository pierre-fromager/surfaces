
#include "suite_fraction.h"

static polynomial_ratio_t r, ra, rb;

void reset_test_fraction()
{
    r = ra = rb = (polynomial_ratio_t){.num = 0, .denom = 1};
}

static int suite_setup(void)
{
    reset_test_fraction();
    return 0;
}

static int suite_teardown(void)
{
    reset_test_fraction();
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_surfaces_fraction_add, "fraction_add"},
    {0, 0},
};

void test_surfaces_fraction_add_suite()
{
    const char *suite_name = "fraction";
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

void test_surfaces_fraction_add()
{
    // 0/1 + 0/1 = 0/1 = 0
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);
    reset_test_fraction();
    // 0/1 + 1/1 = 1/1 = 1
    rb.num = 1;
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 1);
    CU_ASSERT_EQUAL(r.denom, 1);
    reset_test_fraction();
    // 1/1 + 0/1 = 1/1 = 1
    ra.num = 1;
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 1);
    CU_ASSERT_EQUAL(r.denom, 1);
    reset_test_fraction();
    // 1/1 + 1/1 = 2/1 = 2
    ra.num = rb.num = 1;
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 2);
    CU_ASSERT_EQUAL(r.denom, 1);
    reset_test_fraction();
    // 4/2 + 4/2 = 8/2 = 4/1 = 4
    ra.num = rb.num = 4;
    ra.denom = rb.denom = 2;
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 4);
    CU_ASSERT_EQUAL(r.denom, 1);
    reset_test_fraction();
    // 5/10 + 4/11 = 19/22
    ra = (polynomial_ratio_t){.num = 5, .denom = 10};
    rb = (polynomial_ratio_t){.num = 4, .denom = 11};
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 19);
    CU_ASSERT_EQUAL(r.denom, 22);
    reset_test_fraction();
    // 3/5 + 7/17 = 86/85
    ra = (polynomial_ratio_t){.num = 3, .denom = 5};
    rb = (polynomial_ratio_t){.num = 7, .denom = 17};
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 86);
    CU_ASSERT_EQUAL(r.denom, 85);
    // 1/3 - 1/3 = 0
    ra = (polynomial_ratio_t){.num = 1, .denom = 3};
    rb = (polynomial_ratio_t){.num = -1, .denom = 3};
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);
    // -1/3 + 1/3 = 0
    ra = (polynomial_ratio_t){.num = -1, .denom = 3};
    rb = (polynomial_ratio_t){.num = 1, .denom = 3};
    r = fraction_add(ra, rb);
    CU_ASSERT_EQUAL(r.num, 0);
    CU_ASSERT_EQUAL(r.denom, 1);
}
