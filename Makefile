CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ansi
OBJ = pmms.o matrix-builder.o matrix-multiplier.o util.o
EXEC = pmms

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

pmms.o: pmms.c ansi-color.h matrix.h matrix-builder.h matrix-multiplier.h util.h
	$(CC) -c pmms.c $(CFLAGS)

matrix-builder.o: matrix-builder.c util.h matrix.h ansi-color.h
	$(CC) -c matrix-builder.c $(CFLAGS)

matrix-multiplier.o: matrix-multiplier.c matrix.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

util.o: util.c matrix.h ansi-color.h
	$(CC) -c util.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ)

