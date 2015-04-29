HASH_DIR=hash_libs
TARGETS=$(shell ls $(HASH_DIR))

antcrypt_FLAGS=-lcrypto -lm
argon_FLAGS=-lstdc++
argon-aesni_FLAGS=-DUSE_PHSX -lstdc++ -lpthread
argon2d_FLAGS=-lstdc++
argon2d-sse_FLAGS=-DUSE_PHSX -lstdc++ -lpthread
argon2i_FLAGS=-lstdc++
argon2i-sse_FLAGS=-lstdc++ -lpthread
battcrypt_FLAGS=-lstdc++
centrifuge_FLAGS=-lcrypto
gambit_FLAGS=-lstdc++
lyra2_FLAGS=-lgomp
lyra2-sse_FLAGS=-lgomp -DUSE_PHSX
makwa_FLAGS=-lcrypto
pufferfish_FLAGS=-lcrypto
rig_FLAGS=-lm
tortuga_FLAGS=-lm
twocats_FLAGS=-DUSE_PHSX -lcrypto -lpthread
yescrypt_FLAGS=-fopenmp
yescrypt-sse_FLAGS=-fopenmp -DUSE_PHSX
yescrypt-2pw_FLAGS=-fopenmp
yescrypt-2pw-sse_FLAGS=-fopenmp -DUSE_PHSX

#CFLAGS=-O2 -Wall
CFLAGS=-g -Wall
LDFLAGS=-lrt
CC=gcc
#SOURCES=$(wildcard src/*.c)
#OBJECTS=$(SOURCES:.c=.o)

all: hash_libs $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -o tst-$@ src/test.c $^ $(HASH_DIR)/$@/$@.a $(LDFLAGS) $($@_FLAGS)

hash_libs:
	for alg in $(TARGETS) ; do \
		make -C $(HASH_DIR)/$$alg ; \
	done

clean:
	for alg in $(TARGETS) ; do \
		make clean -C $(HASH_DIR)/$$alg ; \
	done
	rm -f src/*.o *~ core tst-*

# ignore build errors
.IGNORE: hash_libs $(TARGETS)

.PHONY: clean default hash_libs
