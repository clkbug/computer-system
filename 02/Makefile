CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -std=c11 -g

HOMEWORK = 02_hw

02_hw: 02_hw.c

.PHONY: clean run debug
clean:
	rm -f 02_hw

run: 02_hw
	./02_hw

debug: 02_hw
	gdb 02_hw
