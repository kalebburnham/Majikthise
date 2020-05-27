UNAME=$(shell uname)

CFLAGS = -Wall
CCFLAGS=-Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter -O3
CC=gcc

DEPS = ctest.h test_rays.h ../src/rays.h
OBJ = main.o test_rays.o ../src/rays.o

all: test

remake: clean all

%.o: %.c $(DEPS)
	$(CC) $(CCFLAGS) -c -o $@ $<

test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o test

clean:
	rm -f test *.o

