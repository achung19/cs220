CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra
DEBUGGINGFLAGS=-g

cTreeTest: CTreeTest.o CTree.o
	$(CC) -o cTreeTest CTreeTest.o CTree.o $(DEBUGGINGFLAGS)

tTreeTest: TTreeTest.o
	$(CC) -o tTreeTest TTreeTest.o $(DEBUGGINGFLAGS)

CTreeTest.o: CTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp $(DEBUGGINGFLAGS)

TTreeTest.o: TTreeTest.cpp Tree.h Tree.inc
	$(CC) $(CFLAGS) -c TTreeTest.cpp $(DEBUGGINGFLAGS)

CTree.o: CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTree.cpp $(DEBUGGINGFLAGS)

clean:
	rm -f *.o tTreeTest cTreeTest *~
