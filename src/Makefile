CC = gcc
CFLAGS = -Wall
DEPS = types.h bitboard.h printer.h conversion.h movegen.h rays.h eval.h
OBJ = main.o bitboard.o printer.o movegen.o rays.o eval.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)
	rm main