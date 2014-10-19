CFLAGS=-O2 -Wall -fexceptions
CC=gcc

OBJ=gambit.o keccak.o

all: gambit.a

gambit.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a

.PHONY: clean
