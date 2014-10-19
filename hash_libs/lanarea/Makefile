CFLAGS=-O2 -Wall
#LDLIBS=-lgcrypt -lssl -lnss3
CC=gcc

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

all: lanarea.a

lanarea.a: libb2/src/.libs/libb2_la-blake2b.o lanarea.o
	ar rcs $@ $^

libb2/src/.libs/libb2_la-blake2b.o:
	(cd libb2; autoreconf; automake --add-missing; ./configure && make)

clean:
	rm -f *.o *~ core *.a
	(cd libb2; make distclean)

.PHONY: clean
