CC       = g++
CPPFLAGS   = -c -Wall -O2

TARGETS=parallel.a

SOURCES=parallel.cpp sha512.cpp

default: $(TARGETS)

parallel.a: $(SOURCES:.cpp=.o)
	ar rcs $@ $^

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
