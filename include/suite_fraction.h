/**
 * @file suite_fraction.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial fractions 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __TEST_SURFACES_SUITE_FRACTION_H__
#define __TEST_SURFACES_SUITE_FRACTION_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fraction.h"

void test_surfaces_fraction_add_suite(void);
void reset_test_fraction(void);

void test_surfaces_fraction_add(void);

#endif // __TEST_SURFACES_SUITE_FRACTION_H__