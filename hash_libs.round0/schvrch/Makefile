CFLAGS=-Wall -O2
CC=gcc

OBJ=schvrch.o

schvrch.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a

.PHONY: clean
