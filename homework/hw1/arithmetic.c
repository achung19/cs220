// Alisen Chung
// achung19

#include <stdio.h>

int endReached = 0;

void printError(void) {
  printf("malformed expression\n");
}

float scanNum(float total, int div) {
  float t;
  int s = scanf("%f", &t);
  
  if(s != 1) {
    printError();
    endReached = 1;
    return 1;
  } else if(div == 0) {
    return total*t;
  } else if(t == 0) {
    printf("division by zero\n");
    endReached = 1;
    return 2;
  } else {
    return total/t;
  }
}

float scanOp(float total, char t, int s) {
  if(s == 0) {
    printError();
    endReached = 1;
    return 1;
  } else if(s == -1) {
    printf("%f\n", total);
    endReached = 1;
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

  printf("Please enter an arithmetic expression using * and / only:\n");
  if(scanf("%f", &result) != 1) {
    printError();
    endReached = 1;
    return 1;
  }

  while(endReached == 0) {
    char temp;
    int scanner = scanf(" %c", &temp);
    
    result = scanOp(result, temp, scanner);
  }
  return result;
}
