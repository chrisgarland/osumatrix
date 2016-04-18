CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = matrix-multiplier.o
EXEC = matrix-multiplier

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

matrix-multiplier.o: matrix-multiplier.c ansi-color.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ)

