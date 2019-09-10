// Alisen Chung
// achung19

#include <stdio.h>

int main(void) {
  float result = 0;
  
  if(scanf("%f", &result) == 0) {
    printError();
    return 0;
  }

  scanOp(result);
  return 0;

}
 
void printError(void) {
  printf("malformed expression");
}

float scanOp(float total) {
  char t;
  int s = scanf(" %c", &t);
  
  if(s == 0) {
    printError();
    return 0;
  } else if(s == -1) {
    printf("%f", total);
    return total;
  } else if(t == "*") {
    return scanNum(total, 0);
  } else if(t == "/") {
    return scanNum(total, 1);
  } else {
    printError();
    return 0;
  }
}
  
float scanNum(float total, int div) {
  float t;
  int s = scanf("%f", &t);
  
  if(s != 1) {
    printError();
    return 0;
  } else if(div == 0) {
    return scanOp(total*t);
  } else if(t == 0) {
    printf("division by zero");
    return 0;
  } else {
    return scanOp(total/t);
  }
}
