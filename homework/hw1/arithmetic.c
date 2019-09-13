// Alisen Chung
// achung19

#include <stdio.h>

// endReached is an integer boolean that holds 0 to continue looping,
// 1 for error reached, and 2 for EOF reached.
int endReached = 0;

// Prints error message
void printError(void) {
  printf("malformed expression\n");
}
/*
 * scanNum takes a float total and an integer boolean div and scans for
 * a float t. scanNum returns the total multiplied or divided by t depending
 * on div. scanNum also checks for invalid inputs and division by 0 and
 * returns an error.
 *
 * total the running total of all operations so far
 * div 0 for multiplication, 1 for division
 */
float scanNum(float total, int div) {
  float t;
  int s = scanf("%f", &t);

  // last input must be an operation so the result is an error
  // regardless of EOF or invalid input
  if(s != 1) {
    printError();
    endReached = 1;
    return 1;  
  } else if(div == 0) { // multiplication
    return total*t;
  } else if(t == 0) { // divide by 0
    printf("division by zero\n");
    endReached = 1;
    return 2;
  } else { // division
    return total/t;
  }
}

/*
 * scanOp takes a float total to pass onto scanNum and scans for a char.
 * If the char is a viable operator, then scanNum is called with that
 * operator in the parameters. If the char is an EOF, then total is returned.
 * Otherwise, an error is returned.
 *
 * total running total to be passed into scanNum
 */
float scanOp(float total) {
  char t;
  int s = scanf(" %c", &t);  

  if(s == 0) {
    printError();
    endReached = 1;
    return 1;
  } else if(s == -1) {
    printf("%f\n", total);
    endReached = 2;
    return total;
  } else if(t == '*') {
    return scanNum(total, 0);
  } else if(t == '/') {
    return scanNum(total, 1);
  } else {
    printError();
    endReached = 1;
    return 1;
  }
}

int main() {
  float result = 0; 

  // Prompt to enter inputs and first scan outside loop
  printf("Please enter an arithmetic expression using * and / only:\n");
  if(scanf("%f", &result) != 1) {
    printError();
    endReached = 1;
    return 1;
  }

  // Repeat while no errors or EOFs are reached
  while(endReached == 0) {
    result = scanOp(result);
  }

  // Check for which value to print
  if(endReached == 1) { // Print error mark
    return result;
  } else { // Print 0 for successful inputs
    return 0;
  }
}
