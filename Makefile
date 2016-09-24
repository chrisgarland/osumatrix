CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
#VPATH = src:../include
#BINDIR = bin/
#SRCDIR = src/
OBJ = src/pmms.o src/matrix-builder.o src/matrix-multiplier.o src/util.o src/process-control.o \
      src/thread-control.o
PMMS_DEPENDENCIES = src/pmms.c include/ansi-color.h include/matrix.h include/matrix-builder.h \
		    include/matrix-multiplier.h include/util.h include/process-control.h \
		    include/thread-control.h
P_CONTROL_DEPEND = src/process-control.c include/subtotal.h include/os-semaphore.h include/matrix.h \
		   include/ansi-color.h
EXEC = bin/pmms
EXTRA_OUTPUT = psout

$(BINDIR)$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

pmms.o: $(PMMS_DEPENDENCIES)
	$(CC) -c pmms.c $(CFLAGS)

matrix-builder.o: src/matrix-builder.c include/util.h include/matrix.h include/ansi-color.h
	$(CC) -c matrix-builder.c $(CFLAGS)

matrix-multiplier.o: src/matrix-multiplier.c include/matrix.h
	$(CC) -c matrix-multiplier.c $(CFLAGS)

util.o: src/util.c include/matrix.h include/ansi-color.h
	$(CC) -c util.c $(CFLAGS)

process-control.o: $(P_CONTROL_DEPEND)
	$(CC) -c process-control.c $(CFLAGS)

thread-control.o: src/thread-control.c include/matrix.h include/subtotal.h include/ansi-color.h
	$(CC) -c thread-control.c $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJ) `find . -name "*$(EXTRA_OUTPUT)*"`

