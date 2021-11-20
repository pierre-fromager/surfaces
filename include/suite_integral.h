/**
 * @file suite_integral.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial integration
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __TEST_SURFACES_SUITE_INTEGRAL_H__
#define __TEST_SURFACES_SUITE_INTEGRAL_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interval.h"
#include "integral.h"
#include "renderer.h"

#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP

void test_surfaces_integral_add_suite(void);
void reset_test_integral(void);

void test_surfaces_integral_ref_o0(void);
void test_surfaces_integral_trapez_o0(void);
void test_surfaces_integral_midpnt_o0(void);
void test_surfaces_integral_simpson_o0(void);
void test_surfaces_integral_factory_riemann_o0(void);
void test_surfaces_integral_ref_o1(void);
void test_surfaces_integral_trapez_o1(void);
void test_surfaces_integral_midpnt_o1(void);
void test_surfaces_integral_factory_o0(void);
void test_surfaces_integral_factory_o1(void);
void test_surfaces_integral_factory_o2(void);
void test_surfaces_integral_factory_o3(void);
void test_surfaces_integral_factory_o1024(void);
void test_surfaces_integral_factory_o2048(void);
void test_surfaces_integral_factory_o4096(void);
void test_surfaces_integral_ref_o2(void);
void test_surfaces_integral_ref_o3(void);
void test_surfaces_integral_ref_o4(void);
void test_surfaces_integral_ref_gmp_int_o4096(void);

#endif // __TEST_SURFACES_SUITE_INTEGRAL_H__
