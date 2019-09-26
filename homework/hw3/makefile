CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

main: word_search.o search_functions.o
	$(CC) -o word_search word_search.o search_functions.o

test: test_search_functions.o search_functions.o
	$(CC) -o test_search_functions test_search_functions.o search_functions.o
	./test_search_functions

test_search_functions.o: test_search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c test_search_functions.c

word_search.o: word_search.c search_functions.h
	$(CC) $(CFLAGS) -c word_search.c

search_functions.o: search_functions.c search_functions.h
	$(CC) $(CFLAGS) -c search_functions.c

clean:
	rm -f *.o word_search test_search_functions
