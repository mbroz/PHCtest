CFLAGS=-Wall -O2
CC=gcc

OBJ=yarn.o

yarn.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a

.PHONY: clean
