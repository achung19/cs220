CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

cTreeTest: CTreeTest.o CTree.o
	$(CC) -o cTreeTest CTreeTest.o CTree.o

tTreeTest: TTreeTest.o CTree.o
	$(CC) -o tTreeTest TTreeTest.o CTree.o

CTreeTest.o: CTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp -g

TTreeTest.o: TTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c TTreeTest.cpp

CTree.o: CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTree.cpp

clean:
	rm -f *.o tTreeTest cTreeTest *~
