CC=g++
CPPFLAGS=-lpthread -std=c++11 -O2
#LIBS=-pthread -lcrypto -lm

TARGETS=argon2i.a

SOURCES_ARGON2I=$(wildcard ref/*.cpp)

default: $(TARGETS)

argon2i.a: $(SOURCES_ARGON2I:.cpp=.o)
	ar rcs $@ $^

clean:
	rm -f ref/*.o $(TARGETS)

.PHONY: clean
