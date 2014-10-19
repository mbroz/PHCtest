# Algorithm Name: Test for MCS_PSW
# Principal Submitter: Mikhail Maslennikov
# Revision: 12.02.2014 

#all: test
all: mcs_phs.a

OBJ=code/mcssha8/mcssha8.o code/mcs_psw/mcs_psw.o

mcs_phs.a: $(OBJ)
	ar rcs $@ $^

clean:
	-rm -f $(OBJ) *.a

test: mcssha8.o mcs_psw.o test.o  
	g++ ./lib/mcssha8.o ./lib/mcs_psw.o ./lib/test.o -o ./bin/test.exe

mcssha8.o: 
	g++ -c ./code/mcssha8/mcssha8.cpp -o ./lib/mcssha8.o

mcs_psw.o: 
	g++ -c ./code/mcs_psw/mcs_psw.cpp -o ./lib/mcs_psw.o

test.o: 
	g++ -c ./code/test/test.cpp -o ./lib/test.o 

