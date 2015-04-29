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

#include <stdlib.h>
#include <ctype.h>
#include "mickey/exceptions.h"
#include "mickey/parser.h"
#include "mickey/print.h"
#include "mickey/util.h"
#include "mickey/primitives.h"

int count(const char *s, int (*check)(int))
{
  int n = 0;
  while ( !empty(s) )
    if ( check(*s++) )
      ++n;
  return n;
}

int all(const char* s, int (*check)(int))
{
  if ( empty(s) )
    return false;

  while ( !empty(s) )
    if ( !check(*s++) )
      return false;
  return true;
}

real_t to_f(const char* s, int radix)
{
  // TODO: Add support for non-decimal radix
  if ( radix != 10 )
    raise(parser_exception("Only radix 10 reals are supported"));

  return atof(s);
}

static integer_t atoi(const char* s, int radix)
{
  return static_cast<integer_t>(strtol(s, static_cast<char**>(NULL), radix));
}

integer_t  to_i(const char* s, int radix)
{
  if ( s == NULL )
    raise(runtime_exception("Cannot convert NULL to INTEGER"));

  int has_sign = (char_in(*s, "+-"));
  int sign = (s[0]=='-'? -1 : 1);

  return sign * atoi(has_sign + s, radix);
}

rational_t to_r(const char* sc, int radix)
{
  char *s = strdup(sc);

  // form: <integer>/<integer>
  char *d = strchr(s, '/');

  if ( d == NULL )
    raise(runtime_exception("Rational number has no divisor"));

  *d = '\0';
  char *numerator = s;
  char *denominator = d+1;

  rational_t r;
  r.numerator = to_i(numerator, radix);
  r.denominator = to_i(denominator, radix);

  free(s);
  return r;
}

bool to_b(const char* s)
{
  return s[1]=='t'? true : false;
}

char to_char(const char* s)
{
  // Example: "#\ "
  // TODO: How will this work? `(display #\<CTRL+V, CTRL+TAB>)´ ?
  if ( strlen(s) == 2 )
    return ' ';

  // Example: "#\A", etc.
  if ( strlen(s) == 3 )
    // TODO: Only allow SPECIFIC character ranges
    return s[2];

  // Example: "#\x28" -> '('
  if ( strlen(s)>3 && s[2] == 'x' && ishex(s+3) ) {
    long code = strtol(s+3, (char**)NULL, 16);

    if ( code > 0x7F ) // U+0000 --- U+007F, i.e., the ASCII repertoire
      raise(runtime_exception("Unicode characters are not suppoted"));

    return static_cast<char>(code);
  }

  // Example: "#\space"
  // TODO: Make ONE giant table that we use for all character mappings
  s += 2;
  std::string lit = tolower(s);

  if ( lit == "space" )     return ' ';
  if ( lit == "tab" )       return '\t';
  if ( lit == "newline" )   return '\n';
  if ( lit == "return"  )   return '\r';
  if ( lit == "null"  )     return '\0';
  if ( lit == "alarm" )     return '\a';
  if ( lit == "backspace" ) return '\x8';
  if ( lit == "escape" )    return '\x1b';
  if ( lit == "delete" )    return '\x7f';

  raise(runtime_exception(format("Unrecognized character literal: #\\%s", s)));
  return '\0'; // make compiler happy
}

cons_t* parse_exact_real(const char* sc, int radix)
{
  if ( radix != 10 )
    raise(parser_exception(
      "Only reals with decimal radix are supported"));

  /*
   * Since the real is already in string form, we can simply turn it into a
   * rational number.
   */
  char *s = strdup(sc);
  char *d = strchr(s, '.');
  *d = '\0';
  const char* left = s;
  const char* right = d+1;

  int decimals = strlen(right);

  /*
   * NOTE: If we overflow here, we're in big trouble.
   * TODO: Throw an error if we overflow.  Or just implement bignums.
   */
  rational_t r;
  r.numerator = to_i(left, radix)*pow10(decimals) + to_i(right, radix);
  r.denominator = pow10(decimals);

  free(s);
  return rational(r, true);
}
