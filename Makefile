CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ansi
OBJ = matrix-multiplier.o matrix-builder.o util.o
EXEC = matrix-multiplier

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

matrix-multiplier.o: matrix-multiplier.c ansi-color.h matrix.h matrix-builder.h util.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

matrix-builder.o: matrix-builder.c util.h matrix.h ansi-color.h
	$(CC) -c matrix-builder.c $(CFLAGS)

util.o: util.c matrix.h ansi-color.h
	$(CC) -c util.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ)

