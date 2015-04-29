/*
 * Mickey Scheme
 *
 * Copyright (C) 2011-2012 Christian Stigen Larsen <csl@sublevel3.org>
 * http://csl.sublevel3.org                              _
 *                                                        \
 * Distributed under the LGPL 2.1; see LICENSE            /\
 * Please post bugfixes and suggestions to the author.   /  \_
 *
 */

#ifndef INC_MICKEY_PARSER_H
#define INC_MICKEY_PARSER_H

#include "mickey/cons.h"

struct program_t {
  environment_t *globals;
  cons_t *root;
  long int parens;
};

/*
 * Parsers
 */
cons_t* parse_string(const char*);
program_t* parse(const std::string& program, environment_t *env);
cons_t* parse_exact_real(const char*, int radix);

/*
 * Predicates
 */
bool isatom(const char*);
bool isbool(const char*);
bool isbytevector(const char*);
bool ischar(const char*);
bool isreal(const char*);
bool ishex(const char*);
bool isinteger(const char*, int radix=10);
bool isrational(const char*);
bool isquasiquote(const char*);
bool issinglequote(const char*);
bool isstring(const char*);
bool isunquote(const char*);
bool isunquote_splicing(const char*);
bool isvector(const char*);
bool isvowel(char);
int isdot(int s);
int ishexdigit(int s);

/*
 * Conversion from text
 */
bool to_b(const char*);
char literal_to_char(const char*);
char to_char(const char*);
real_t to_f(const char*, int radix = 10);
enum type_t to_type_t(const char*);
integer_t  to_i(const char*, int radix = 10);
rational_t to_r(const char*, int radix = 10);

/*
 * Pattern matchers
 */
int all(const char* s, int (*check)(int));
int count(const char* s, int (*check)(int));

#endif
