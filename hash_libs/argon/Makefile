CC=gcc
CPPFLAGS=-O3 -maes -mavx -std=c++11
LIBS=-pthread -lcrypto -lm

EXE = argon.a

#OBJ = Argon-Optimized.o
OBJ = argon-ref.o

default: $(EXE)

argon.a: $(OBJ)
	#$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)
	ar rcs $@ $^

clean:
	rm -f *.o $(OBJ) $(EXE)
