#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10]){
  char newMatrix[10][10];
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      newMatrix[col][9-row] = matrix[row][col];
    }
  }
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      matrix[row][col] = newMatrix[row][col];
    }
  }
  return;
}
