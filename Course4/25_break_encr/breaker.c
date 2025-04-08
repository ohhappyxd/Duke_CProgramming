#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t findMax(int counts[]) {
  size_t maxIdx = 0;
  int maxCount = 0;
  for (size_t i = 0; i < 26; i++) {
    if (counts[i] > maxCount) {
      maxIdx = i;
      maxCount = counts[i];
    }
  }
  return maxIdx;
}

int breaker(FILE * f) {
  // Array to store results
  int counts[26] = {0};
  // Count appearences
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      int idx = c - 'a';
      counts[idx] += 1;
    }
  }
  // Find most frequent letter
  size_t max = findMax(counts);
  // Calculate key, e is at index 4, so key is (26 + max - 4) % 26
  return (int) (26 + max - 4) % 26;
}
int main(int argc, char ** argv) {
  //check for argument counts
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  // handle file opening error
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    return EXIT_FAILURE;
  }
  int key = breaker(f);
  if (key < 26 && key >= 0) {
    fprintf(stdout, "%i\n", key);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Could not calculate key\n");
    return EXIT_FAILURE;
  }
}
