CC = gcc
CFLAGS = -Wall
DEPS = bitboard.h printer.h types.h conversion.h
OBJ = main.o bitboard.o printer.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^