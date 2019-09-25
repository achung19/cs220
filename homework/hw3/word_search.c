// word_search.c
// Alisen Chung
// achung19

#include <stdio.h>
#include <string.h>
#include "search_functions.h"


/*
 * This is the HW3 main function that performs a word search.
 */
int main(int argc, char* argv[]) {
  if (argc == 0) {
    printf("Please enter a command line argument.\n");
    return 1;
  }

  char grid[MAX_SIZE][MAX_SIZE];
  int n = populate_grid(grid, argv[0]);
  if (n == -1) {
    printf("Grid file failed to open.\n");
    return n;
  } else if (n == -2) {
    printf("Invalid Grid.\n");
    return n;
  }

  FILE* output_file = fopen("Output.txt", "w");
  if (output_file == NULL) {
    printf("Output file failed to open.\n");
    return -1;
  }

  char words[][MAX_SIZE];
  int num_words = 0;
  while (scanf("%s" &words[i]) != -1) {
    num_words++;
  }

  for (int i = 0; i < num_words; i++) {
    find_all(grid, n, words[i], output_file);
  }

  return 0;
}

