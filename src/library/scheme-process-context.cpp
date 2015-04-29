/*
 * Mickey Scheme
 *
 * Copyright (C) 2011-2013 Christian Stigen Larsen <csl@sublevel3.org>
 * http://csl.sublevel3.org                              _
 *                                                        \
 * Distributed under the LGPL 2.1; see LICENSE            /\
 * Please post bugfixes and suggestions to the author.   /  \_
 *
 */

#include <stdlib.h>
#include <string.h>
#include "mickey/mickey.h"

extern char **environ;

extern "C" {

cons_t* proc_get_environment_variable(cons_t* p, environment_t*)
{
  assert_length(p, 1);
  assert_type(STRING, car(p));
  const char* s = getenv(car(p)->string);
  return s? string(s) : boolean(false);
}

cons_t* proc_get_environment_variables(cons_t* p, environment_t*)
{
  assert_length(p, 0);
  cons_t *r = list(NULL);

  // count environment variables
  int count=0;
  while ( environ[count] != NULL ) ++count;

  // add to output as (key . value)
  for ( int n=count-1; n>=0; --n ) {
    // split "key=val" into ("key" . "val")
    char *key = static_cast<char*>(malloc(1+strlen(environ[n])));
    strcpy(key, environ[n]);

    // find '='
    char *value = key;
    while ( *value ) {
      if ( *value == '=' ) {
        *value++ = '\0';
        break;
      } else ++value;
    }

    // standard doesn't say anything about ENV='',
    // so guess we'll just add empty string then
    r = cons(cons(string(key), string(value)), r);
    free(key);
  }

  return r;
}

cons_t* proc_command_line(cons_t* p, environment_t*)
{
  assert_length(p, 0);
  cons_t *r = list();

  for ( int n=global_opts.argc-1; n>=0; --n )
    r = cons(string(global_opts.argv[n]), r);

  return r;
}

cons_t* proc_exit(cons_t* p, environment_t*)
{
  assert_length(p, 0, 1);

  /*
   * TODO: Run all outstanding dynamic-wind AFTER-procs
   */

  int code = EXIT_SUCCESS;

  if ( length(p) == 1 ) {
    if ( integerp(car(p)) )
      code = car(p)->number.integer;
    else if ( realp(car(p)) )
      code = static_cast<int>(car(p)->number.real);
    else
      code = !boolean_false(car(p))? EXIT_SUCCESS : EXIT_FAILURE;
  }

  ::exit(code);
  return unspecified();
}

cons_t* proc_emergency_exit(cons_t* p, environment_t*)
{
  assert_length(p, 0, 1);

  int code = EXIT_SUCCESS;

  if ( length(p) == 1 ) {
    if ( integerp(car(p)) )
      code = car(p)->number.integer;
    else if ( realp(car(p)) )
      code = static_cast<int>(car(p)->number.real);
    else
      code = !boolean_false(car(p))? EXIT_SUCCESS : EXIT_FAILURE;
  }

  ::_exit(code);
  return unspecified();
}

}
