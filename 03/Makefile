CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g -lm
SHELL = /bin/bash

HOMEWORK = 03_hw

03_hw: 03_hw.c 03_asm.s
	$(CC) -o $@ $^ $(CFLAGS)
	$(CC) -S $^ $(CFLAGS)

03_hw_opt: 03_hw.c 03_asm.s
	$(CC) -o $@ $^ $(CFLAGS) -O2

.PHONY: clean run runopt test debug
clean:
	rm -f 03_hw 03_hw_opt

run: 03_hw
	./03_hw

runopt: 03_hw_opt
	./03_hw_opt

test: 03_hw 03_hw_opt
	vimdiff <(./03_hw) <(./03_hw_opt)
	echo ok

debug: 03_hw
	gdb 03_hw
