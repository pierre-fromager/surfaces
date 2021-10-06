
#ifndef __TEST_SURFACES_SUITE_DERIVATIVE_H__
#define __TEST_SURFACES_SUITE_DERIVATIVE_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/derivative.h"
#include "../../src/solution.h"

void test_surfaces_derivative_add_suite(void);
void reset_test_derivative(void);

void test_surfaces_derivative_derivate_o0(void);
void test_surfaces_derivative_derivate_o1(void);
void test_surfaces_derivative_derivate_o2(void);
void test_surfaces_derivative_derivate_o3(void);
void test_surfaces_derivative_antiderivate_o0(void);
void test_surfaces_derivative_antiderivate_o1(void);
void test_surfaces_derivative_antiderivate_o2(void);
void test_surfaces_derivative_antiderivate_o3(void);

#endif // __TEST_SURFACES_SUITE_DERIVATIVE_H__
