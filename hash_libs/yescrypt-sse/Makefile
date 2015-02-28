CC=gcc
CPPFLAGS=-Wall -march=native -O2 -funroll-loops -fomit-frame-pointer -fopenmp

TARGETS=yescrypt-sse.a

SOURCES_YESCRYPT=phc.c yescrypt-common.c sha256.c yescrypt-ref.c
SOURCES_YESCRYPT_SSE=phc.c yescrypt-common.c sha256.c yescrypt-simd.c

default: $(TARGETS)

yescrypt.a: $(SOURCES_YESCRYPT:.c=.o)
	ar rcs $@ $^

yescrypt-sse.a: $(SOURCES_YESCRYPT_SSE:.c=.o)
	ar rcs $@ $^

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
