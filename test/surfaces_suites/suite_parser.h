
#ifndef __TEST_SURFACES_SUITE_PARSER_H__
#define __TEST_SURFACES_SUITE_PARSER_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/parser.h"

#define POLY_MAX_ORDER 1024 * 4

void test_surfaces_parser_add_suite(void);
void reset_test_parser(void);

void test_surfaces_parser_o0(void);
void test_surfaces_parser_o1(void);
void test_surfaces_parser_o2(void);
void test_surfaces_parser_o10(void);
void test_surfaces_parser_o100(void);
void test_surfaces_parser_o1000(void);
void test_surfaces_parser_o4096(void);

#endif // __TEST_SURFACES_SUITE_PARSER_H__