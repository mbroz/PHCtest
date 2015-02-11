CFLAGS=-O2 -Wall
CC=gcc

OBJ=pomelo_sse2.o

pomelo.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a

.PHONY: clean
