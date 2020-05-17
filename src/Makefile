CC = gcc
CFLAGS = -Wall
DEPS = types.h bitboard.h printer.h conversion.h movegen.h
OBJ = main.o bitboard.o printer.o movegen.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^