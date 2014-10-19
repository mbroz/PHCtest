CFLAGS=-Wall -std=c99 -msse4.2 -O3 -funroll-loops
CC=gcc

VER=Rig_v2-ref
OBJ=$(VER)/rig.o $(VER)/blake_impl.o $(VER)/BLAKE/blake2b-ref.o

rig2.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -f *.o *~ core *.a $(OBJ)

.PHONY: clean
