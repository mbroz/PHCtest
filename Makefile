HASH_DIR=hash_libs
TARGETS=$(shell ls $(HASH_DIR))

antcrypt_FLAGS=-lcrypto -lm
argon_FLAGS=-lstdc++
battcrypt_FLAGS=-lstdc++
centrifuge_FLAGS=-lcrypto
gambit_FLAGS=-lstdc++
makwa_FLAGS=-lcrypto
#pufferfish_FLAGS=-lcrypto
rig_FLAGS=-lm
tortuga_FLAGS=-lm
twocats_FLAGS=-lcrypto -lpthread
yescrypt_FLAGS=-fopenmp

#CFLAGS=-O2 -Wall
CFLAGS=-g -Wall
CC=gcc
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: hash_libs $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -o tst-$@ $^ $($@_FLAGS) $(HASH_DIR)/$@/$@.a

hash_libs:
	for alg in $(TARGETS) ; do \
		make -C $(HASH_DIR)/$$alg ; \
	done

clean:
	for alg in $(TARGETS) ; do \
		make clean -C $(HASH_DIR)/$$alg ; \
	done
	rm -f src/*.o *~ core tst-*

.PHONY: clean default hash_libs
