#|

Mickey R7RS Scheme

Copyright (C) 2012-2013 Christian Stigen Larsen <csl@sublevel3.org>
http://csl.sublevel3.org                              _
                                                       \
Distributed under the LGPL 2.1; see LICENSE            /\
Please post bugfixes and suggestions to the author.   /  \_

|#
(define-library (scheme inexact)
  (import (only (scheme base) define)
          (mickey library))
  (export acos
          asin
          atan
          ceiling
          cos
          exp
          floor
          log
          sin
          sqrt
          tan)
  (begin
    (open-internal-library "libscheme-math.so" 'lazy 'global)
    (define exp     (bind-procedure "proc_exp"))
    (define log     (bind-procedure "proc_log"))
    (define sin     (bind-procedure "proc_sin"))
    (define cos     (bind-procedure "proc_cos"))
    (define tan     (bind-procedure "proc_tan"))
    (define asin    (bind-procedure "proc_asin"))
    (define acos    (bind-procedure "proc_acos"))
    (define atan    (bind-procedure "proc_atan"))
    (define sqrt    (bind-procedure "proc_sqrt"))
    (define ceiling (bind-procedure "proc_ceil"))
    (define floor   (bind-procedure "proc_floor")))
