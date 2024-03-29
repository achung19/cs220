// word_search.c
// Alisen Chung
// achung19

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search_functions.h"

/*
 * This is the HW3 main function that performs a word search.
 */
int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Please enter a command line argument.\n");
    return 1;
  }

  // Populate grid, return error if needed.
  char grid[MAX_SIZE][MAX_SIZE];
  int n = populate_grid(grid, argv[1]);
  if (n == -1) {
    printf("Grid file failed to open.\n");
    return -1;
  } else if (n == -2) {
    printf("Invalid grid.\n");
    return -2;
  }

  // Scans for words until EOF is passed.
  char words[MAX_SIZE+1];
  while (scanf(" %s",words) != -1) {
    find_all(grid, n, words, stdout);
  }
  
  return 0;
}
