CC := gcc
CFLAGS := -Wall -Werror -Wpedantic -g

define scm
(use-modules (srfi srfi-1))

(define problems '(11 12 13 14 15 16 17 18 19 20 21 22))
(define (n-to-src n) (format #f "08.~a.c" n))
(define (n-to-target n) (format #f "08.~a" n))
(define targets (map n-to-target problems))
(define srcs (map n-to-src problems))
(define targets-and-srcs (zip targets srcs))

(define (stringify arg)
	(define t (car arg))
	(define s (cadr arg))
	(format #f
		"~a : ~a csapp.h\n\t$(CC) $(CFLAGS) -o ~a ~a\n\n" t s t s))


(gmk-eval (format #f "all: ~a" (string-join targets)))
(gmk-eval (string-join (map stringify targets-and-srcs)))
(gmk-eval (format #f ".PHONY: clean\nclean:\n\trm -f ~a" (string-join targets)))

endef

t := $(guile $(scm))
