UNAME=$(shell uname)

CFLAGS = -Wall
CCFLAGS=-Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3
CC=gcc

TESTDEPS = test_eval.h test_rays.h test_movegen.h
TESTOBJ = test_eval.o test_rays.o test_movegen.o

SRCDEPS = ../src/bitboard.h ../src/eval.h ../src/movegen.h ../src/printer.h ../src/rays.h ../src/sorters.h
SRCOBJ = ../src/bitboard.o ../src/eval.o ../src/movegen.o ../src/printer.o ../src/rays.o ../src/sorters.c

DEPS = ctest.h $(TESTDEPS) $(SRCDEPS)
OBJ = main.o $(TESTOBJ) $(SRCOBJ)

all: test

remake: clean all

%.o: %.c $(DEPS)
	$(CC) $(CCFLAGS) -c -o $@ $<

test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o test

clean:
	rm -f test *.o

