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
#include "mickey/exceptions.h"
#include "mickey/parser.h"
#include "mickey/util.h"

int isdot(int s)
{
  return s == '.';
}

int ishexdigit(int s)
{
  return isdigit(s) ||
    (s>='a' && s<='f') ||
    (s>='A' && s<='F');
}

bool ishex(const char* s)
{
  return !empty(s) && all(s, ishexdigit);
}

bool isinteger(const char* s, int radix)
{
  int sign = (s[0]=='-' || s[0]=='+');
  return !empty(s) && all(s+sign, radix<=10? isdigit : ishexdigit);
}

bool isrational(const char* sc)
{
  char *s = strdup(sc);

  // form: <integer>/<integer>
  char *d = strchr(s, '/');

  if ( d == NULL )
    return false;

  *d = '\0';
  char *numerator = s;
  char *denominator = d+1;

  bool ret = isinteger(numerator) && isinteger(denominator);
  free(s);
  return ret;
}

bool isbool(const char* s)
{
  return s[0]=='#' && (s[1]=='t' || s[1]=='f');
}

bool ischar(const char* s)
{
  return s[0]=='#' && s[1]=='\\' && s[2]!='\0';
}

bool isreal(const char* s)
{
  // TODO: Make pattern complete
  // Pattern now: [+-]?[0-9]*\.?[0-9]+f?
  size_t dots   = count(s, isdot);
  size_t sign   = (s[0]=='-' || s[0]=='+');
  size_t digits = count(s, isdigit);
  size_t last_f = (s[0]? s[strlen(s)-1] == 'f' : 0);

  /*
   * The parts of a good looking floating point
   * number are: [+-] [0-9] [.] [0-9] [f]
   *
   * Now, the number of digits + MAX ONE dot
   * + MAX ONE trailing 'f' should equal the
   * length of the string -- for a finely formatted
   * floating point number.
   *
   * I know this is a stretch, but I'm NOT going
   * to the pain of installing a regex just to parse
   * a frickin number :-)
   *
   */

  if ( strlen(s+sign) == (digits + (dots==1) + last_f) )
    return digits>0 && (dots==1 || last_f); // or else it's an ordinary integer
  else
    return false;
}

bool isodd(int n)
{
  return n & 1;
}

bool isstring(const char* s)
{
  size_t l = strlen(s);

  // a string must start and end with quote: "..."
  if ( s==NULL || l<=1 || s[0]!='"' || s[l-1]!='"' ) {

    /*
     * If token begins with a doublequote, then we've
     * got a malformed string.
     */
    if ( s[0]=='"' )
      raise(compiler_exception("Not a valid string: " + std::string(s)));

    return false;
  }

  // count quotes
  size_t quotes = 0;

  for ( const char *p=s; p < s+l; ++p ) {
    switch ( *p ) {
      case '\\':
        // skip escaped character
        ++p;
        continue;
      case '"':
        ++quotes;

        // when we've hit ending quote, check that
        // we're at the end-position
        if ( quotes == 2 )
          return strlen(p+1) == 0;

        break;
      default:
        continue;
        break;
    }
  }

  // should've finished at second quote over, so must be error
  return false;
}

/*
 * ATOM := <alpha> <alphanum>* |
 *         '|' <alpha | space> <alphanum | space>* '|'
 */
bool isatom(const char* s)
{
  // normal atom
  if ( s[0]!='|' )
    return isalpha(s[0]) && (empty(s+1) ? true : all(s+1, isalnum));

  const size_t l = strlen(s);

  // format: |long atom form|
  if ( s[1]!='|' && s[l-1]=='|' ) {
    char* t = strdup(s);
    t[l-1]='\0';
    bool r = isatom(t+1);
    free(t);
    return r;
  }

  return false;
}

bool isvector(const char* s)
{
  return s[0]=='#' && s[1]=='(';
}

bool isbytevector(const char* s)
{
  return s[0]=='#' && s[1]=='u'
      && s[2]=='8' && s[3]=='(';
}

bool isvowel(char c)
{
  switch ( c ) {
  case 'a': case 'e': case 'i':
  case 'o': case 'u': case 'y':
    return true;
  default:
    return false;
  }
}

bool issinglequote(const char* s)
{
  return *s=='\'';
}

bool isquasiquote(const char* s)
{
  return *s == '`';
}

bool isunquote(const char* s)
{
  return *s == ',' && *(s+1) != '@';
}

bool isunquote_splicing(const char *s)
{
  return *s == ',' && *(s+1) == '@';
}
