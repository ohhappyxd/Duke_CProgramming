#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

#define ADD_LENGTH 7
char * computeOutputFileName(const char * inputName) {
  char * outFileName = malloc((strlen(inputName) + 1 + ADD_LENGTH) * sizeof(*outFileName));
  strcpy(outFileName, inputName);
  strcat(outFileName, ".counts");
  return outFileName;
}
