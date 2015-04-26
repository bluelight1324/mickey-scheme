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

#ifndef INC_MICKEY_H
#define INC_MICKEY_H

#define MICKEY_VERSION_MAJOR 0
#define MICKEY_VERSION_MINOR 1

const char MICKEY_NAME[] = "Mickey Scheme";
const char MICKEY_COPYRIGHT[] = "(C) 2011-2015 Christian Stigen Larsen";

/*
 * The following files are REQUIRED to link to when making
 * dynamic Mickey Scheme libraries.
 *
 * TODO: Reduce this list as much as possible.
 */

#include "apply.h"
#include "arguments.h"
#include "assertions.h"
#include "backtrace.h"
#include "circular.h"
#include "cons.h"
#include "debug.h"
#include "eval.h"
#include "evlis.h"
#include "exceptions.h"
#include "file-io.h"
#include "import.h"
#include "options.h"
#include "parser.h"
#include "primitives.h"
#include "print.h"
#include "syntax-rules.h"
#include "tokenizer.h"
#include "util.h"

#endif
