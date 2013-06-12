;; Mickey Scheme library structure

;; These are the libraries loaded by the REPL.
;;
;; It would be better to move these off the index and into a (mickey repl)
;; library instead).
;;
(define-repl-imports
  (scheme base)
  (scheme cxr)
  (scheme write)
  (scheme char)
  (scheme load)
  (scheme process-context)
  (scheme repl))

;; List of available libraries and their locations
(define-library-index
  ((c stdio)                 "c/stdio.scm")
  ((cross-platform sdl)      "cross-platform/sdl.scm")
  ((experimental endianness) "experimental/endianness.scm")
  ((experimental eval-with-continuation) "experimental/eval-with-continuation.scm")
  ((experimental unit-testing) "experimental/unit-testing.scm")
  ((implementation version)  "implementation/version.scm")
  ((maclisp)                 "maclisp/maclisp.scm")
  ((mickey environment)      "mickey/environment.scm")
  ((mickey gensym)           "mickey/gensym.scm")
  ((mickey internals)        "mickey/internals.scm")
  ((mickey library)          "mickey/library.scm")
  ((mickey misc)             "mickey/misc.scm")
  ((portable atom?)          "portable/atom?.scm")
  ((portable booleans)       "portable/booleans.scm")
  ((portable flatten)        "portable/flatten.scm")
  ((portable gensym)         "portable/gensym.scm")
  ((portable print)          "portable/print.scm")
  ((portable sequence)       "portable/sequence.scm")
  ((prng lcg)                "prng/lcg.scm")
  ((scheme base)             "scheme/base/base.scm")
  ((scheme case-lambda)      "scheme/case-lambda.scm")
  ((scheme char)             "scheme/char.scm")
  ((scheme complex)          "scheme/complex.scm")
  ((scheme cxr)              "scheme/cxr.scm")
  ((scheme eval)             "scheme/eval.scm")
  ((scheme file)             "scheme/file.scm")
  ((scheme inexact)          "scheme/inexact.scm")
  ((scheme inquiry)          "scheme/inquiry.scm")
  ((scheme lazy)             "scheme/lazy.scm")
  ((scheme load)             "scheme/load.scm")
  ((scheme process-context)  "scheme/process-context.scm")
  ((scheme r5rs)             "scheme/r5rs.scm")
  ((scheme read)             "scheme/read.scm")
  ((scheme repl)             "scheme/repl.scm")
  ((scheme time)             "scheme/time.scm")
  ((scheme write)            "scheme/write.scm")
  ((srfi 0)                  "srfi/srfi-0.scm")
  ((srfi 1)                  "srfi/srfi-1.scm")
  ((srfi 4)                  "srfi/srfi-4.scm")
  ((srfi 8)                  "srfi/srfi-8.scm")
  ((srfi 16)                 "srfi/srfi-16.scm")
  ((srfi 98)                 "srfi/srfi-98.scm")
  ((srfi 112)                "srfi/srfi-112.scm")
  ((test unit-test)          "test/unit-test.scm")
  ((unix dlopen)             "")
  ((unix exit)               "unix/exit.scm")
  ((unix fork)               "unix/fork.scm")
  ((unix kill)               "unix/kill.scm")
  ((unix signal)             "unix/signal.scm")
  ((unix time)               "unix/time.scm")
  ((unix uname)              "unix/uname.scm")
  ((unix unistd)             "unix/unistd.scm")
  ((unix wait)               "unix/wait.scm"))
