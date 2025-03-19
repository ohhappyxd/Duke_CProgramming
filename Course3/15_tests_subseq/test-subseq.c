#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int array1[] = {1, 2, 3, 4, 3};
  int array2[] = {-1, -2, -3, 1};
  int array3[] = {-1, 1, -10, 10};
  int array4[] = {0, 0, 0};
  int array5[] = {0, 15, 15, 15};
  int array6[] = {};
  int array7[] = {-10, -1, 0, 1000, -2};
  int array8[] = {-3, -4, -5};
  
  if(maxSeq(NULL,0)){
    return EXIT_FAILURE;
  }
  if(maxSeq(array1, 5)!= 4){
    return EXIT_FAILURE;
  }
  if(maxSeq(array2, 4) != 2) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array3, 4) != 2) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 3) != 1) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array5, 4) != 2) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array6, 0) != 0) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array7, 5) != 4) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array8, 3) != 1) {
    return EXIT_FAILURE;
  }
}
