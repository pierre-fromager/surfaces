
#ifndef __TEST_SURFACES_SUITE_RIEMANNSUM_H__
#define __TEST_SURFACES_SUITE_RIEMANNSUM_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/interval.h"
#include "../../src/riemannsum.h"
//#include "../../src/integral.h"

#define IL_L 0.0f
#define IL_STEP 1.0f
#define IL_H 5.0f / IL_STEP

void test_surfaces_riemannsum_add_suite(void);
void reset_test_riemannsum(void);

void test_surfaces_riemannsum_left_o0(void);
void test_surfaces_riemannsum_right_o0(void);
void test_surfaces_riemannsum_trap_o0(void);
void test_surfaces_riemannsum_rect_o0(void);
void test_surfaces_riemannsum_mp_o0(void);
void test_surfaces_riemannsum_left_o1(void);
void test_surfaces_riemannsum_right_o1(void);
void test_surfaces_riemannsum_trap_o1(void);
void test_surfaces_riemannsum_rect_o1(void);
void test_surfaces_riemannsum_mp_o1(void);

#endif // __TEST_SURFACES_SUITE_RIEMANNSUM_H__
