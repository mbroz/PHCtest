all: rig.a

rig.a: blake2b.o rig.o
	ar rcs $@ $^

phc_rig: main.o rig.o blake2b.o
	gcc -Ofast -march=native -std=c99 main.o rig.o blake2b.o -o phc_rig -lm

main.o: main.c
	gcc -Ofast -march=native -std=c99 -c main.c

rig.o: rig.c
	gcc -Ofast -march=native -std=c99 -c rig.c
   
blake2b.o:
	gcc -Ofast -march=native -std=c99 -c BLAKE/blake2b.c

clean:
	rm -rf *.o *.a phc_rig


