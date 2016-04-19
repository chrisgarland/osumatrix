CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = matrix-multiplier.o matrix-builder.o
EXEC = matrix-multiplier

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

matrix-multiplier.o: matrix-multiplier.c ansi-color.h matrix.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

matrix-builder.o: matrix-builder.c util.h matrix.h
	$(CC) -c matrix-builder.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ)

