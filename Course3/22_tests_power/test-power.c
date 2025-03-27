#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

unsigned power (unsigned x, unsigned y);

int main(void) {
  bool allCorrect = true;
  if (power(0, 0)!= 1) {
    printf("Failed test case 1\n");
    allCorrect = false;
  }
  if (power(2, 1) != 2) {
    printf("Failed test case 2\n");
    allCorrect = false;
  }
  if (power(1, 10) != 1) {
    printf("Failed test case 3\n");
    allCorrect = false;
  }
  if (power(0, 5) != 0) {
    printf("Failed test case 4\n");
    allCorrect = false;
  }
  if (power(5, 0) != 1) {
    printf("Failed test case 5\n");
    allCorrect = false;
  }
  if (power(4294967295U, 1) != 4294967295U) {
    printf("Failed test case 6\n");
    allCorrect = false;
  }
  if (power(2, 31) != 2147483648U) {
    printf("Failed test case 7\n");
    allCorrect = false;
  }
  if (allCorrect) {
    return EXIT_SUCCESS;
  } else if (!allCorrect) {
    return EXIT_FAILURE;
  }
  
}
