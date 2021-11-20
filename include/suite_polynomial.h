/**
 * @file suite_polynomial.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial basics 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __TEST_SURFACES_SUITE_POLYNOMIAL_H__
#define __TEST_SURFACES_SUITE_POLYNOMIAL_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "polynomial.h"
#include "renderer.h"

#define TEST_SURFACE_POLY_CHAR_BUFF_LEN 1024 * 4

void test_surfaces_polynomial_add_suite(void);
void reset_test_polynomial(void);

void test_surfaces_polynomial_reset(void);
void test_surfaces_polynomial_gethighestfactor(void);
void test_surfaces_polynomial_addratio(void);
void test_surfaces_polynomial_o0(void);
void test_surfaces_polynomial_o1(void);
void test_surfaces_polynomial_o2(void);
void test_surfaces_polynomial_o3(void);
void test_surfaces_polynomial_gmp_int(void);
void test_surfaces_polynomial_gmpfr_o0(void);
void test_surfaces_polynomial_gmpfr_o64(void);
void test_surfaces_polynomial_gmpfr_o128(void);
void test_surfaces_polynomial_gmpfr_o256(void);
void test_surfaces_polynomial_gmpfr_o512(void);
void test_surfaces_polynomial_gmpfr_o1024(void);
void test_surfaces_polynomial_gmpfr_o2048(void);
void test_surfaces_polynomial_gmpfr_o4096(void);
void test_surfaces_polynomial_add_o0(void);
void test_surfaces_polynomial_add_o1(void);
void test_surfaces_polynomial_add_o2(void);
void test_surfaces_polynomial_sub_o0(void);
void test_surfaces_polynomial_sub_o1(void);
void test_surfaces_polynomial_sub_o2(void);
void test_surfaces_polynomial_sub_o2a(void);

#endif // __TEST_SURFACES_SUITE_POLYNOMIAL_H__
