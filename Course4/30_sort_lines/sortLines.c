#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This FUNCTION will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

size_t readFileToArray(char ***inputArray, FILE *file){
  char *line = NULL;
  size_t len = 0;
  size_t lines_count = 0;
  char **lines = NULL;

  while (getline(&line, &len, file) != -1){
    char **temp = realloc(lines, (lines_count + 1) * sizeof(char *));
    if (!temp) {
      perror("Unable to allocate memory");
      free(line);
      free(lines);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    lines = temp;
    lines[lines_count] = line;
    line = NULL;
    len = 0;
    lines_count ++;
  }

  free(line);
  *inputArray = lines;
  return lines_count;
}

FILE * getFileFromArg(char * arg) {
  FILE *file = fopen(arg, "r");
  if (!file) {
    perror("Unable to open file");
    exit(EXIT_FAILURE);
  }
  return file;
}

int main(int argc, char ** argv) {
  char ** inputArray = NULL;
  // handle stdin
  if (argc == 1) {
    size_t line_counts = readFileToArray(&inputArray, stdin);
    sortData(inputArray, line_counts);
  }
  // handle files
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE *file = getFileFromArg(argv[i]);
      inputArray = NULL;
      size_t line_counts = readFileToArray(&inputArray, file);
      sortData(inputArray, line_counts);
      fclose(file);
    }
  }
  
  return EXIT_SUCCESS;
}
