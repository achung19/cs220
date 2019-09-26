// search_functions.c
// Alisen Chung
// achung19

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search_functions.h"

/* 
 * Converts s to all lowercase characters. Returns -1 if there are
 * non-alphabetical characters, 0 otherwise.
 */
int convert_lowercase(char s[]) {
  for (int i = 0; i < (int) strlen(s); i++) {
    if (s[i] >= 65 && s[i] <= 90) {
      s[i] += 'a' - 'A';
    } else if (s[i] < 97 || s[i] > 122) {
      return -1;
    }
  }
  return 0;
}

/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */
int populate_grid(char grid[][MAX_SIZE], char filename_to_read_from[]){
  
  FILE * file = fopen(filename_to_read_from, "r");
  if (file == NULL) {
    return -1;
  }

  char s[MAX_SIZE+2];
  int n = 0;
  if (fscanf(file, " %s", s) != 1) {
    fclose(file);
    return -2;
  }
  if ((int) strlen(s) > MAX_SIZE || strlen(s) == 0) {
    fclose(file);
    return -2;
  } else if (convert_lowercase(s) == -1) {
    fclose(file);
    return -2;
  }
  n = strlen(s);
  strcpy(grid[0], s);

  for (int i = 1; i < n; i++) {
    if (fscanf(file, " %s", s) != 1) {
      fclose(file);
      return -2;
    }
    if ((int) strlen(s) != n || convert_lowercase(s) == -1) {
      fclose(file);
      return -2;
    }
    strcpy(grid[i], s);
  }
  
  char end[2];
  fscanf(file, "%2c", end);
  if (end[1] != 10 || end[0] != 10){
    fclose(file);
    return -2;
  }
  
  fclose(file);
  return n;
}

/*
 * Searches for a word in a grid from left to right, starting at the specified location.
 */
int find_at_horizontal(char grid[][MAX_SIZE], int n, char word[], int loc[]) {

  if (loc[1]+(int) strlen(word) > n) {
    return 0;
  }

  for (int i = 0; i < (int) strlen(word); i++) {
    if (grid[loc[0]][loc[1]+i] != word[i]) {
      return 0;
    }
  }
  return 1;
}

/*
 * Searches for a word in a grid from top to bottom, starting at the specified location.
 */
int find_at_vertical(char grid[][MAX_SIZE], int n, char word[], int loc[]) {

  if (loc[0]+(int) strlen(word) > n) {
    return 0;
  }

  for (int i = 0; i < (int) strlen(word); i++) {
    if (grid[loc[0]+i][loc[1]] != word[i]) {
      return 0;
    }
  }
  return 1;
}

/* 
 * Finds words in grid from left to right.
 */
int find_right(char grid[][MAX_SIZE], int n, char word[], FILE *write_to){
  int count = 0;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int arr[] = {i,j};
      if (find_at_horizontal(grid, n, word, arr) == 1) {
	fprintf(write_to, "%s %d %d R\n", word, i, j);
	count++;
      }
    }
  }
  return count;
}


/* 
 * Finds words in grid from right to left by reversing string and using 
 * find_right logic.
 */
int find_left (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){
  char rev_word[MAX_SIZE+1];
  for (int i = 0; i < (int) strlen(word); i++) {
    rev_word[i] = word[strlen(word)-1-i];
  }
  rev_word[(int) strlen(word)] = '\0';

  int count = 0;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int arr[] = {i,j};
      if (find_at_horizontal(grid, n, rev_word, arr) == 1) {
	fprintf(write_to, "%s %d %d L\n", word, i, j+(int) strlen(word)-1);
	count++;
      }
    }
  }
  return count;
}


/* 
 * Finds words in grid from top to bottom. 
 */
int find_down (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){
  int count = 0;
  
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      int arr[] = {i,j};
      if (find_at_vertical(grid, n, word, arr) == 1) {
	fprintf(write_to, "%s %d %d D\n", word, i, j);
	count++;
      }
    }
  }
  return count;
}


/* 
 * Finds words in grid from bottom to top by reversing string and sing
 * find_down logic. 
 */
int find_up (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){
  char rev_word[MAX_SIZE+1];
  for (int i = 0; i < (int) strlen(word); i++) {
    rev_word[i] = word[(int) strlen(word)-1-i];
  }
  rev_word[strlen(word)] = '\0';

  int count = 0;
  
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      int arr[] = {i,j};
      if (find_at_vertical(grid, n, rev_word, arr) == 1) {
	fprintf(write_to, "%s %d %d U\n", word, i+(int) strlen(word)-1, j);
	count++;
      }
    }
  }
  return count;
}


/* 
 * Calls and sums up all find functions.
 */
int find_all  (char grid[][MAX_SIZE], int n, char word[], FILE *write_to) {
  int count = find_right(grid, n, word, write_to);
  count += find_left(grid, n, word, write_to);
  count += find_down(grid, n, word, write_to);
  count += find_up(grid, n, word, write_to);
  if (count == 0) {
    fprintf(write_to, "%s - Not Found\n", word);
  }
  return count;
} 


/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match. The definition of this function is provided 
 * for you.
 */
int file_eq(char lhs_name[], char rhs_name[]) {
  FILE* lhs = fopen(lhs_name, "r");
  FILE* rhs = fopen(rhs_name, "r");

  // don't compare if we can't open the files
  if (lhs == NULL || rhs == NULL) return 0;

  int match = 1;
  // read until both of the files are done or there is a mismatch
  while (!feof(lhs) || !feof(rhs)) {
	if (feof(lhs) ||                      // lhs done first
		feof(rhs) ||                  // rhs done first
		(fgetc(lhs) != fgetc(rhs))) { // chars don't match
	  match = 0;
	  break;
	}
  }
  fclose(lhs);
  fclose(rhs);
  return match;
}

