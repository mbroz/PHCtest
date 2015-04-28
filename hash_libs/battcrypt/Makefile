CC       = g++
CPPFLAGS   = -c -Wall -O2

TARGETS=battcrypt.a

SOURCES=battcrypt.cpp blowfish.cpp sha512.cpp

default: $(TARGETS)

battcrypt.a: $(SOURCES:.cpp=.o)
	ar rcs $@ $^

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
