#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (x == 0 && y == 0) {
    return 1;
  }
  if (y == 0) {
    return 1;
  }
  if (x == 0) {
    return 0;
  }
  else {
    return x * power(x, y - 1);
  }
}
