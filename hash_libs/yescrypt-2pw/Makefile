CC=gcc
CPPFLAGS=-Wall -O2 -fopenmp

TARGETS=yescrypt-2pw.a

SOURCES_YESCRYPT=phc.c yescrypt-common.c sha256.c yescrypt-opt.c

default: $(TARGETS)

yescrypt-2pw.a: $(SOURCES_YESCRYPT:.c=.o)
	ar rcs $@ $^

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
