CC=g++
CPPFLAGS=-lpthread -std=c++11 -O2
#LIBS=-pthread -lcrypto -lm

TARGETS=argon2d.a

SOURCES_ARGON2D=$(wildcard ref/*.cpp)

default: $(TARGETS)

argon2d.a: $(SOURCES_ARGON2D:.cpp=.o)
	ar rcs $@ $^

clean:
	rm -f ref/*.o $(TARGETS)

.PHONY: clean
