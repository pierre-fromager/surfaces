
#ifndef __TEST_SURFACES_SUITE_INTEGRAL_H__
#define __TEST_SURFACES_SUITE_INTEGRAL_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/interval.h"
#include "../../src/integral.h"

#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP

void test_surfaces_integral_add_suite(void);
void reset_test_integral(void);

void test_surfaces_integral_ref_o0(void);
void test_surfaces_integral_trapez_o0(void);
void test_surfaces_integral_midpnt_o0(void);
void test_surfaces_integral_riemann_left_o0(void);
void test_surfaces_integral_riemann_right_o0(void);
void test_surfaces_integral_riemann_trap_o0(void);
void test_surfaces_integral_riemann_rect_o0(void);
void test_surfaces_integral_riemann_mp_o0(void);
void test_surfaces_integral_simpson_o0(void);
void test_surfaces_integral_factory_o0(void);
void test_surfaces_integral_ref_o1(void);
void test_surfaces_integral_trapez_o1(void);
void test_surfaces_integral_midpnt_o1(void);
void test_surfaces_integral_riemann_left_o1(void);
void test_surfaces_integral_riemann_right_o1(void);
void test_surfaces_integral_riemann_trap_o1(void);
void test_surfaces_integral_riemann_rect_o1(void);
void test_surfaces_integral_riemann_mp_o1(void);
void test_surfaces_integral_factory_o1(void);

#endif // __TEST_SURFACES_SUITE_INTEGRAL_H__
