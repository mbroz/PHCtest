CFLAGS=-O3

TEST_OBJECTS=test.o tortuga.a

LIBS=-lm

all: tortuga.a

tortuga.a: turtle.o tortuga.o phs.o
	ar rcs $@ $?

test: $(TEST_OBJECTS)
	$(CC) $? -o $@ $(LIBS)

clean:
	rm -f *.o *.a test
