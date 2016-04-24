CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
OBJ = pmms.o matrix-builder.o matrix-multiplier.o util.o process-control.o
PMMS_DEPENDENCIES = pmms.c ansi-color.h matrix.h matrix-builder.h \
		    matrix-multiplier.h util.h process-control.h
P_CONTROL_DEPEND = process-control.c subtotal.h os-semaphore.h matrix.h \
		   ansi-color.h
EXEC = pmms
EXTRA_OUTPUT = psout

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

pmms.o: $(PMMS_DEPENDENCIES)
	$(CC) -c pmms.c $(CFLAGS)

matrix-builder.o: matrix-builder.c util.h matrix.h ansi-color.h
	$(CC) -c matrix-builder.c $(CFLAGS)

matrix-multiplier.o: matrix-multiplier.c matrix.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

util.o: util.c matrix.h ansi-color.h
	$(CC) -c util.c $(CFLAGS)

process-control.o: $(P_CONTROL_DEPEND)
	$(CC) -c process-control.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ) $(EXTRA_OUTPUT)

