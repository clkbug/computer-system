CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c11 -g
SHELL = /bin/bash

HOMEWORK = 02_hw

02_hw: 02_hw.c
	$(CC) $(CFLAGS) -o $@ $^

02_hw_opt: 02_hw.c
	$(CC) $(CFLAGS) -O2 -o $@ $^

.PHONY: clean run runopt test debug
clean:
	rm -f 02_hw 02_hw_opt

run: 02_hw
	./02_hw

runopt: 02_hw_opt
	./02_hw_opt

test: 02_hw 02_hw_opt
	vimdiff <(./02_hw) <(./02_hw_opt)
	echo ok

debug: 02_hw
	gdb 02_hw
