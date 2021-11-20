
#ifndef __TEST_SURFACES_SUITE_ROOTS_H__
#define __TEST_SURFACES_SUITE_ROOTS_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "roots.h"

void test_surfaces_roots_add_suite(void);
void reset_test_roots(void);

void test_surfaces_roots_factory_o0(void);
void test_surfaces_roots_factory_o1(void);
void test_surfaces_roots_factory_o2(void);
void test_surfaces_roots_factory_o2a(void);
void test_surfaces_roots_factory_o3(void);
void test_surfaces_roots_factory_o4(void);

#endif // __TEST_SURFACES_SUITE_ROOTS_H__