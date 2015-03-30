CC=g++
CPPFLAGS=-m64 -mavx -std=c++11 -pthread -O3
#LIBS=-pthread -lcrypto -lm

TARGETS=argon2i-sse.a

SOURCES_ARGON2I=$(wildcard opt-sse/*.cpp)

default: $(TARGETS)

argon2i-sse.a: $(SOURCES_ARGON2I:.cpp=.o)
	ar rcs $@ $^

clean:
	rm -f opt-sse/*.o $(TARGETS)

.PHONY: clean
