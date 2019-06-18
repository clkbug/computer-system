CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c11 -g -lm
SHELL = /bin/bash

HOMEWORK = 05_hw

05_hw: 05_hw.c
	$(CC) -o $@ $^ $(CFLAGS)

05_hw_opt: 05_hw.c
	$(CC) -o $@ $^ $(CFLAGS) -O2

.PHONY: clean run runopt test debug
clean:
	rm -f 05_hw 05_hw_opt

run: 05_hw
	./05_hw

runopt: 05_hw_opt
	./05_hw_opt

test: 05_hw 05_hw_opt
	vimdiff <(./05_hw) <(./05_hw_opt)
	echo ok

debug: 05_hw
	gdb 05_hw
