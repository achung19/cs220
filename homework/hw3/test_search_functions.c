// test_search_functions.c
// Alisen Chung
// achung19

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "search_functions.h"

/* 
 * Declarations for tester functions whose definitions appear below.
 * (You will need to fill in the function definition details, at the
 * end of this file, and add comments to each one.) 
 * Additionally, for each helper function you elect to add to the 
 * provided search_functions.h, you will need to supply a corresponding
 * tester function in this file.  Add a declaration for it here, its
 * definition below, and a call to it where indicated in main.
 */
void test_file_eq();      // This one is already fully defined below.
void test_convert_lowercase();
void test_populate_grid();
void test_find_at_horizontal();
void test_find_at_vertical();
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();


/*
 * Main method which calls all test functions.
 */
int main() {
  printf("Testing file_eq...\n");
  test_file_eq();
  printf("Passed file_eq test.\n\n");

  printf("Running search_functions tests...\n");
  test_populate_grid();
  test_find_right();
  test_find_left();
  test_find_down();
  test_find_up();
  test_find_all();

  /* You may add calls to additional test functions here. */
  test_convert_lowercase();
  test_find_at_horizontal();
  test_find_at_vertical();

  printf("Passed search_functions tests!!!\n");
}



/*
 * Test file_eq on same file, files with same contents, files with
 * different contents and a file that doesn't exist.
 * Relies on files test1.txt, test2.txt, test3.txt being present.
 */
void test_file_eq() {
  FILE* fptr = fopen("test1.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  fptr = fopen("test2.txt", "w");
  fprintf(fptr, "this\nis\na different test\n");
  fclose(fptr);

  fptr = fopen("test3.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  assert( file_eq("test1.txt", "test1.txt"));
  assert( file_eq("test2.txt", "test2.txt"));
  assert(!file_eq("test2.txt", "test1.txt"));
  assert(!file_eq("test1.txt", "test2.txt"));
  assert( file_eq("test3.txt", "test3.txt"));
  assert( file_eq("test1.txt", "test3.txt"));
  assert( file_eq("test3.txt", "test1.txt"));
  assert(!file_eq("test2.txt", "test3.txt"));
  assert(!file_eq("test3.txt", "test2.txt"));
  assert(!file_eq("", ""));  // can't open file
}


void test_convert_lowercase(){
  
  char test1[] = "TESTING";
  char test2[] = "Testing";
  char test3[] = "testing";
  char err1[] = "!@#$%";
  char err2[] = "test err";
  char err3[] = "Abc!@#";
  char err4[] = "123";
  
  int test1_val = convert_lowercase(test1);
  int test2_val = convert_lowercase(test2);
  int test3_val = convert_lowercase(test3);
  int err1_val = convert_lowercase(err1);
  int err2_val = convert_lowercase(err2);
  int err3_val = convert_lowercase(err3);
  int err4_val = convert_lowercase(err4);
  
  assert(strcmp(test1, test2) == 0);
  assert(strcmp(test2, test3) == 0);
  assert(strcmp(test1, test3) == 0);
  assert(test1_val == 0);
  assert(test2_val == 0);
  assert(test3_val == 0);
  assert(err1_val == -1);
  assert(err2_val == -1);
  assert(err3_val == -1);
  assert(err4_val == -1);
}

void test_populate_grid(){
  FILE* file = fopen("testgrid.txt", "w");
  fprintf(file, "abc\ndef\nghi\n\n");
  fclose(file);

  char test_grid[MAX_SIZE][MAX_SIZE];
  int n = populate_grid(test_grid, "testgrid.txt");

  assert(n == 3);
  assert(test_grid[0][0] == 'a');
  assert(test_grid[0][1] == 'b');
  assert(test_grid[0][2] == 'c');
  assert(test_grid[1][0] == 'd');
  assert(test_grid[1][1] == 'e');
  assert(test_grid[1][2] == 'f');
  assert(test_grid[2][0] == 'g');
  assert(test_grid[2][1] == 'h');
  assert(test_grid[2][2] == 'i');  
}

void test_find_at_horizontal(){
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c'}};
  int temp[] = {0,0};
  int bad_temp[] = {1, 0};

  assert(find_at_horizontal(test_grid, 3, "abc", temp) == 1);
  assert(find_at_horizontal(test_grid, 3, "aaa", temp) == 0);
  assert(find_at_horizontal(test_grid, 3, "aaaaaa", temp) == 0);
  assert(find_at_horizontal(test_grid, 3, "abc", bad_temp) == 0);
}

void test_find_at_vertical(){
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a'}, {'b'}, {'c'}};
  int temp[] = {0,0};
  int bad_temp[] = {0, 1};

  assert(find_at_vertical(test_grid, 3, "abc", temp) == 1);
  assert(find_at_vertical(test_grid, 3, "aaa", temp) == 0);
  assert(find_at_vertical(test_grid, 3, "aaaaaa", temp) == 0);
  assert(find_at_vertical(test_grid, 3, "abc", bad_temp) == 0);
}

void test_find_right(){
  FILE* output_file = fopen("output_test_right.txt", "w");
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'a', 'b', 'c'}};
  
  assert(find_right(test_grid, 3, "abc", output_file) == 2);
  assert(find_right(test_grid, 3, "def", output_file) == 1);
  assert(find_right(test_grid, 3, "ghi", output_file) == 0);
  assert(find_right(test_grid, 3, "zz", output_file) == 0);
  fclose(output_file);
  assert(file_eq("output_test_right.txt", "expected_output_right.txt"));
}

void test_find_left(){
  FILE* output_file = fopen("output_test_left.txt", "w");
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'a', 'b', 'c'}};
  
  assert(find_left(test_grid, 3, "cba", output_file) == 2);
  assert(find_left(test_grid, 3, "fed", output_file) == 1);
  assert(find_left(test_grid, 3, "ihg", output_file) == 0);
  assert(find_left(test_grid, 3, "zz", output_file) == 0);
  fclose(output_file);
  assert(file_eq("output_test_left.txt", "expected_output_left.txt"));
}

void test_find_down(){
  FILE* output_file = fopen("output_test_down.txt", "w");
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'd', 'a'}, {'b', 'e', 'b'}, {'c', 'f', 'c'}};
  
  assert(find_down(test_grid, 3, "abc", output_file) == 2);
  assert(find_down(test_grid, 3, "def", output_file) == 1);
  assert(find_down(test_grid, 3, "ghi", output_file) == 0);
  assert(find_down(test_grid, 3, "zz", output_file) == 0);
  fclose(output_file);
  assert(file_eq("output_test_down.txt", "expected_output_down.txt"));
}

void test_find_up(){
  FILE* output_file = fopen("output_test_up.txt", "w");
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'd', 'a'}, {'b', 'e', 'b'}, {'c', 'f', 'c'}};
  
  assert(find_up(test_grid, 3, "cba", output_file) == 2);
  assert(find_up(test_grid, 3, "fed", output_file) == 1);
  assert(find_up(test_grid, 3, "ihg", output_file) == 0);
  assert(find_up(test_grid, 3, "zz", output_file) == 0);
  fclose(output_file);
  assert(file_eq("output_test_up.txt", "expected_output_up.txt"));
}


void test_find_all(){
  FILE* output_file = fopen("output_test.txt", "w");
  char test_grid[MAX_SIZE][MAX_SIZE] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
  
  assert(find_all(test_grid, 3, "abc", output_file) == 1);
  assert(find_all(test_grid, 3, "fed", output_file) == 1);
  assert(find_all(test_grid, 3, "adg", output_file) == 1);
  assert(find_all(test_grid, 3, "heb", output_file) == 1);
  assert(find_all(test_grid, 3, "def", output_file) == 1);
  assert(find_all(test_grid, 3, "ifc", output_file) == 1);
  assert(find_all(test_grid, 3, "cfi", output_file) == 1);
  assert(find_all(test_grid, 3, "cdg", output_file) == 0);
  assert(find_all(test_grid, 3, "aeh", output_file) == 0);
  assert(find_all(test_grid, 3, "cfg", output_file) == 0);
  assert(find_all(test_grid, 3, "fea", output_file) == 0);
  assert(find_all(test_grid, 3, "abg", output_file) == 0);
  assert(find_all(test_grid, 3, "zz", output_file) == 0);
  fclose(output_file);
  assert(file_eq("output_test.txt", "expected_output.txt"));
}

