
CC=gcc

CFLAGS=-std=c99 -mavx2 -O3 -funroll-loops

all: rig

rig: main.o rig.o blake_impl.o blake2b-ref.o
	$(CC) main.o rig.o blake_impl.o blake2b-ref.o -o rig

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

rig.o: rig.c
	$(CC) $(CFLAGS) -c rig.c

blake_impl.o: blake_impl.c
	$(CC) $(CFLAGS) -c blake_impl.c

blake2b-ref.o: ./BLAKE/blake2b-ref.c
	$(CC) $(CFLAGS) -c ./BLAKE/blake2b-ref.c

clean:
	rm -rf *o rig
