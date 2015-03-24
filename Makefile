HASH_DIR=hash_libs
TARGETS=$(shell ls $(HASH_DIR))

antcrypt_FLAGS=-lcrypto -lm
argon_FLAGS=-lstdc++
argon-aesni_FLAGS=-lstdc++ -lpthread
argon2d_FLAGS=-lstdc++
argon2i_FLAGS=-lstdc++
battcrypt_FLAGS=-lstdc++
centrifuge_FLAGS=-lcrypto
gambit_FLAGS=-lstdc++
lyra2_FLAGS=-lgomp
lyra2-sse_FLAGS=-lgomp
makwa_FLAGS=-lcrypto
pufferfish_FLAGS=-lcrypto
rig_FLAGS=-lm
tortuga_FLAGS=-lm
twocats_FLAGS=-lcrypto -lpthread
yescrypt_FLAGS=-fopenmp
yescrypt-sse_FLAGS=-fopenmp

#CFLAGS=-O2 -Wall
CFLAGS=-g -Wall
LDFLAGS=-lrt
CC=gcc
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: hash_libs $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -o tst-$@ $^ $(LDFLAGS) $($@_FLAGS) $(HASH_DIR)/$@/$@.a

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
