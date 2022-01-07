//Andrew Cornelio
//acornel9

#include <stdio.h>
#include <string.h>

int main() {

  char sign;
  float temp = 0;
  float result = 0;

  printf("Please enter an arithmetic expression using * and / only:\n");
  
  if(scanf("%f", &result) != 1) {
    printf("malformed expression\n");
    return 1;
  }

  int input_s = scanf("%c", &sign);
  while(sign == ' ' || sign == '\t' || sign == '\n') {
    input_s = scanf("%c", &sign);
    if(input_s == -1) {
      printf("%f\n", result);
      return 0;
    }
  }
  int input_t = scanf("%f", &temp);
  
  while(input_s != -1) {
    if((sign != '/' && sign != '*') || input_t != 1) {
      printf("malformed expression\n");
      return 1;
    }
    else if(sign == '/' && temp == 0) {
      printf("division by zero\n");
      return 2;
    }
    else {
      if(sign == '/') {
        result /= temp;
      }
      else {
        result *= temp;
      }
    }

    input_s = scanf("%c", &sign);
    while(sign == ' ' || sign == '\t' || sign == '\n') {
      input_s = scanf("%c", &sign);
      if(input_s == -1) {
        printf("%f\n", result);
      return 0;
      }
    }
    input_t = scanf("%f", &temp);
  }
  printf("%f\n", result);
  return 0;
}
