CC=gcc
CPPFLAGS_REF=-std=c99 -Wall -pedantic -O2 -fopenmp -DnPARALLEL=1
CPPFLAGS_SSE=-std=c99 -Wall -pedantic -O3 -msse2 -ftree-vectorizer-verbose=1 -fopenmp -funroll-loops -march=native -Ofast -mprefer-avx128 -Wno-unused-variable -DnPARALLEL=1

TARGETS=lyra2.a lyra2-sse.a

SOURCES_LYRA2=Lyra2.c Sponge.c
SOURCES_LYRA2_SSE=sse/Lyra2.c sse/Sponge.c

default: $(TARGETS)

lyra2.a: $(SOURCES_LYRA2:.c=.o)
	ar rcs $@ $^

lyra2-sse.a: $(SOURCES_LYRA2_SSE:.c=.o)
	ar rcs $@ $^

sse/%.o: sse/%.c
	$(CC) $(CPPFLAGS_SSE) $< -c -o $@

%.o: %.c
	$(CC) $(CPPFLAGS_REF) $< -c -o $@

clean:
	rm -f *.o sse/*.o $(TARGETS)

.PHONY: clean
