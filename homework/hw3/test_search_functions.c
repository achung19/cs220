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
void test_find_at_vertical()
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();


/*
 * Main method which calls all test functions.
 */
int main(void) {
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
  
  char test1 = "TESTING";
  char test2 = "Testing";
  char test3 = "testing";
  char err1 = "!@#$%";
  char err2 = "test err";
  char err3 = "Abc!@#";
  char err4 = "123";
  
  int test1_val = convert_lowercase(test1);
  int test2_val = convert_lowercase(test2);
  int test3_val = convert_lowercase(test3);
  int err1_val = convert_lowercase(err1);
  int err2_val = onvert_lowercase(err2);
  int err3_val = convert_lowercase(err3);
  int err4_val = convert_lowercase(err4);
  
  assert(strcmp(test1, test2) == 0);
  assert(strcmp(test2, test3) == 0);
  assert(strcmp(test1, test3) == 0);
  assert(test1_val == 0);
  assert(test2_val == 0);
  assert(test3_val == 0);
  assert(err1 == -1);
  assert(err2 == -1);
  assert(err3 == -1);
  assert(err4 == -1);
}

void test_populate_grid(){

  assert(1);  //replace this stub!

}

void test_find_at_horizontal(){

  assert(1);

}

void test_find_at_vertical(){

  assert(1);

}

void test_find_right(){

  assert(1);  //replace this stub!

}


void test_find_left(){

  assert(1);  //replace this stub!
}


void test_find_down(){

  assert(1);  //replace this stub!

}


void test_find_up(){

  assert(1);  //replace this stub!

}


void test_find_all(){

  assert(1);  //replace this stub!

}

