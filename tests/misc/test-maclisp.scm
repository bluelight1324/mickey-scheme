(import (scheme base)
        (scheme write)
        (test unit-test)
        (maclisp))

(test (eq 1 1) #t)
(test (eq 1 2) #f)
(test (let ((v 0)) (aset' v 123) v) 123)
(test (explode 'hello) '(h e l l o))
(test (implode '(h e l l o)) 'hello)
(test (implode (cdr (explode 'hello))) 'ello)
(test (numberp 123) #t)
(test (numberp 'abc) #f)
(test (exploden 'abba) '(97 98 98 97))

(let ((foo '(bar t baz 3 hunoz "Huh?")))
  (test (get foo 'baz) 3)
  (test (get foo 'hunoz) "Huh?")
  (test (get foo 'zoo) nil))

(test (cond (#f 'broken) (t 'works)) 'works)
(test (cond (#t 'works) (t 'broken)) 'works)
(test (null nil) t)

(test (labels
        ((x 'x)
         (y 'y))
        (list x y)) '(x y))

(define foo2 '(bar t))
(test (putprop foo2 3 'bazz) 3)
(test (get foo2 'bazz) 3)
