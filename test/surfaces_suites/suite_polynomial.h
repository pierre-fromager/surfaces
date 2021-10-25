
#ifndef __TEST_SURFACES_SUITE_POLYNOMIAL_H__
#define __TEST_SURFACES_SUITE_POLYNOMIAL_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "../../src/polynomial.h"
#include "../../src/renderer.h"

#define TEST_SURFACE_POLY_CHAR_BUFF_LEN  1024 * 10

void test_surfaces_polynomial_add_suite(void);
void reset_test_polynomial(void);

void test_surfaces_polynomial_reset(void);
void test_surfaces_polynomial_addratio(void);
void test_surfaces_polynomial_o0(void);
void test_surfaces_polynomial_o1(void);
void test_surfaces_polynomial_o2(void);
void test_surfaces_polynomial_o3(void);
void test_surfaces_polynomial_o4097(void);

#endif // __TEST_SURFACES_SUITE_POLYNOMIAL_H__
