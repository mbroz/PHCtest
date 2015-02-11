CC        = cc
CFLAGS    = -g -Wall -pedantic -O3 -march=native
LIBS      = -lcrypto

#all:  pfcrypt-ref pfkdf-ref
all: pufferfish.a

pufferfish.a: pufferfish-ref.o itoa64.o api-ref.o
	ar rcs $@ reference/pufferfish-ref.o common/itoa64.o common/api-ref.o

pfcrypt-ref: pfcrypt-ref.o pufferfish-ref.o itoa64.o api-ref.o
	$(CC) -o pfcrypt-ref examples/pfcrypt-ref.o reference/pufferfish-ref.o common/itoa64.o common/api-ref.o $(LIBS)

pfkdf-ref: pfkdf-ref.o pufferfish-ref.o itoa64.o api-ref.o
	$(CC) -o pfkdf-ref examples/pfkdf-ref.o reference/pufferfish-ref.o common/itoa64.o common/api-ref.o $(LIBS)

pfcrypt-ref.o:
	$(CC) -c $(CFLAGS) -o examples/pfcrypt-ref.o examples/pfcrypt.c

pufferfish-ref.o:
	$(CC) -c $(CFLAGS) -o reference/pufferfish-ref.o reference/pufferfish.c

pfkdf-ref.o:
	$(CC) -c $(CFLAGS) -o examples/pfkdf-ref.o examples/pfkdf.c

api-ref.o:
	$(CC) -c $(CFLAGS) -o common/api-ref.o common/api.c

itoa64.o:
	$(CC) -c $(CFLAGS) -o common/itoa64.o common/itoa64.c

clean:
	rm -f pfcrypt-ref pfkdf-ref examples/*.o common/*.o reference/*.o optimized/*.o *.a

distclean: clean

