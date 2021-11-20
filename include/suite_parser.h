/**
 * @file suite_parser.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial parser
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __TEST_SURFACES_SUITE_PARSER_H__
#define __TEST_SURFACES_SUITE_PARSER_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

#define POLY_MAX_ORDER 1024 * 4

/**
 * @brief add parser suite to tests
 * 
 */
void test_surfaces_parser_add_suite(void);

/**
 * @brief reset test
 * 
 */
void reset_test_parser(void);

/**
 * @brief test parser polynomial order 0
 * 
 */
void test_surfaces_parser_o0(void);
/**
 * @brief test parser polynomial order 1
 * 
 */
void test_surfaces_parser_o1(void);
/**
 * @brief test parser polynomial order 2
 * 
 */
void test_surfaces_parser_o2(void);
/**
 * @brief test parser polynomial order 10
 * 
 */
void test_surfaces_parser_o10(void);
/**
 * @brief test parser polynomial order 100
 * 
 */
void test_surfaces_parser_o100(void);
/**
 * @brief test parser polynomial order 1000
 * 
 */
void test_surfaces_parser_o1000(void);
/**
 * @brief test parser polynomial order 4096
 * 
 */
void test_surfaces_parser_o4096(void);

#endif // __TEST_SURFACES_SUITE_PARSER_H__