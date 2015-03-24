CC=gcc
CPPFLAGS_REF=-Wall -O2 -Wno-unused-variable
CPPFLAGS_SSE=-Wall -O2 -msse2 -Wno-unused-variable

TARGETS=pomelo.a

SOURCES_POMELO=pomelo_x64.c
SOURCES_POMELO_SSE=pomelo_sse2.c

default: $(TARGETS)

pomelo.a: $(SOURCES_POMELO:.c=.o)
	ar rcs $@ $^

pomelo-sse.a: $(SOURCES_POMELO_SSE:.c=.o)
	ar rcs $@ $^

pomelo_sse2.o: pomelo_sse2.c
	$(CC) $(CPPFLAGS_SSE) $< -c -o $@

pomelo_x64.o: pomelo_x64.c
	$(CC) $(CPPFLAGS_REF) $< -c -o $@

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
