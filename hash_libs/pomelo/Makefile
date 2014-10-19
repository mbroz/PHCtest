CFLAGS=-O2 -Wall
CC=gcc

OBJ=pomelo.o

pomelo.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a

.PHONY: clean
