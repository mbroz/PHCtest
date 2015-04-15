CC=gcc
CPPFLAGS=-Wall -march=native -O2 -funroll-loops -fomit-frame-pointer -fopenmp

TARGETS=yescrypt-2pw-sse.a

SOURCES_YESCRYPT_SSE=phc.c yescrypt-common.c sha256.c yescrypt-simd.c

default: $(TARGETS)

yescrypt-2pw-sse.a: $(SOURCES_YESCRYPT_SSE:.c=.o)
	ar rcs $@ $^

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
