#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n) {
  if (array == NULL) {
    return 0;
  }
  if (n == 0) {
    return 0;
  }
  int counter = 1;
  int max = 1;
  for (size_t i = 0; i < n-1; i++) {
    int current = array[i];
    int next = array[i+1];
    if (next > current) {
      counter += 1;
      if (counter > max) {
	max = counter;
      }
    } else {
	counter = 1;
    }
  }
  return max; 
}
