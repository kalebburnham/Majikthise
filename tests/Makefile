UNAME=$(shell uname)

CFLAGS = -Wall
CCFLAGS=-Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3
CC=gcc

TESTDEPS = test_rays.h test_movegen.h
TESTOBJ = test_rays.o test_movegen.o

SRCDEPS = ../src/bitboard.h ../src/movegen.h ../src/printer.h ../src/rays.h
SRCOBJ = ../src/bitboard.o ../src/movegen.o ../src/printer.o ../src/rays.o

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

