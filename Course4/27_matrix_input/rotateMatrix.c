#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 10
#define LINE_LENGTH (MATRIX_SIZE + 1)

void rotate(char matrix[MATRIX_SIZE][MATRIX_SIZE]){
  char newMatrix[MATRIX_SIZE][MATRIX_SIZE];
  for (int row = 0; row < MATRIX_SIZE; row++) {
    for (int col = 0; col < MATRIX_SIZE; col++) {
      newMatrix[col][9-row] = matrix[row][col];
    }
  }
  for (int row = 0; row < MATRIX_SIZE; row++) {
    for (int col = 0; col < MATRIX_SIZE; col++) {
      matrix[row][col] = newMatrix[row][col];
    }
  }
  return;
}

void printMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix fileName.txt\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "Could not open file %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  char matrix[MATRIX_SIZE][MATRIX_SIZE];
  char buffer[LINE_LENGTH + 2];
  for (int i = 0; i < MATRIX_SIZE; i++) {
    if (!fgets(buffer, sizeof(buffer), f)){
      fprintf(stderr, "File has fewer than 10 lines\n");
      fclose(f);
      return EXIT_FAILURE;
    }
    size_t len = strlen(buffer);
    if (len != LINE_LENGTH || buffer[LINE_LENGTH - 1] != '\n'){
      fprintf(stderr, "Error: line %d must be exactly 10 characters followed by a newline\n", i + 1);
      fclose(f);
      return EXIT_FAILURE;
    }
    memcpy(matrix[i], buffer, MATRIX_SIZE);
  }
  if (fgets(buffer, sizeof(buffer), f)) {
    fprintf(stderr, "Error: file has more than 10 lines\n");
    fclose(f);
    return EXIT_FAILURE;
  }
  rotate(matrix);
  printMatrix(matrix);
  return EXIT_SUCCESS;
}
