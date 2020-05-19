CC = gcc
CFLAGS = -Wall
DEPS = types.h bitboard.h printer.h conversion.h movegen.h rays.h
OBJ = main.o bitboard.o printer.o movegen.o rays.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^