/**
 * @file suite_intersect.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial intersections
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __TEST_SURFACES_SUITE_INTERSECT_H__
#define __TEST_SURFACES_SUITE_INTERSECT_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "intersect.h"

/**
 * @brief add intersect suite to tests
 * 
 */
void test_surfaces_intersect_add_suite(void);

/**
 * @brief reset intersect test
 * 
 */
void reset_test_intersect(void);

/**
 * @brief test intersect polynomial order 0
 * 
 */
void test_surfaces_poly_intersect_o2(void);

#endif // __TEST_SURFACES_SUITE_INTERSECT_H__