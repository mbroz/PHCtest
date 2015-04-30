HASH_DIR=hash_libs
TARGETS=$(shell ls $(HASH_DIR))

antcrypt_FLAGS=-lcrypto -lm
argon_FLAGS=-DUSE_PHSX -lstdc++
argon-aesni_FLAGS=-DUSE_PHSX -lstdc++ -lpthread
argon2d_FLAGS=-DUSE_PHSX -lstdc++
argon2d-sse_FLAGS=-DUSE_PHSX -lstdc++ -lpthread
argon2i_FLAGS=-DUSE_PHSX -lstdc++
argon2i-sse_FLAGS=-DUSE_PHSX -lstdc++ -lpthread
battcrypt_FLAGS=-lstdc++
centrifuge_FLAGS=-lcrypto
gambit_FLAGS=-lstdc++
lyra2_FLAGS=-DUSE_PHSX -lgomp
lyra2-sse_FLAGS= -DUSE_PHSX -lgomp
makwa_FLAGS=-lcrypto
pufferfish_FLAGS=-lcrypto
rig_FLAGS=-lm
tortuga_FLAGS=-lm
twocats_FLAGS=-DUSE_PHSX -lcrypto -lpthread
yescrypt_FLAGS=-DUSE_PHSX -fopenmp
yescrypt-sse_FLAGS=-DUSE_PHSX -fopenmp
yescrypt-2pw_FLAGS=-DUSE_PHSX -fopenmp
yescrypt-2pw-sse_FLAGS=-DUSE_PHSX -fopenmp

CFLAGS=-g -Wall
LDFLAGS=-lrt
CC=gcc
SOURCES=src/test.c

all: hash_libs $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -o tst-$@ $(SOURCES) $^ $(HASH_DIR)/$@/$@.a $(LDFLAGS) $($@_FLAGS)

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
