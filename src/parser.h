/**
 * @file parser.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief polynomial equation parser
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _SURFACES_PARSER_
#define _SURFACES_PARSER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "polynomial.h"

#define PARSER_MAX_MATCH 100
#define PARSER_MEMBER_MAX_LEN 50
#define PARSER_TERMS_MAX_MATCHES 20
#define PARSER_MAX_ERROR_MSG 0x1000
#define PARSER_TERMS_PATTERN "([+-]?[^-+]+)"
#define PARSER_TERMS_PATTERN_ENF "([+-]?(?:(?:\\d+x\\^\\d+)|(?:\\d+x)|(?:\\d+)|(?:x)))"
#define PARSER_PATTERN_EXP "^"
#define PARSER_PATTERN_X "x"
#define PARSER_PATTERN_X_EXP PARSER_PATTERN_X PARSER_PATTERN_EXP
#define PARSER_PATTERN_DIV "/"
#define PARSER_PATTERN_MINUS "-"
#define PARSER_PATTERN_PLUS "+"
#define PARSER_ERR_MSG_COMPILE "Regex error compiling '%s': %s\n"
#define PARSER_STR_FMT "%s"
#define PARSER_SUBSTR_FMT "%.*s"

int parser_parse(char *eq, polynomial_t *p);

#endif // _SURFACES_PARSER_