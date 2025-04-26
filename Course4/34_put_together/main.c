#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Error opening file");
    return NULL;
  }
  counts_t * counts = createCounts();
  char * name = NULL;
  size_t size = 0;
  ssize_t nread;
  while ((nread = getline(&name, &size, f)) != -1) {
    name[strcspn(name, "\n")] = '\0';
    char * value = lookupValue(kvPairs, name);
    addCount(counts, value);
  }
  free(name);
  fclose(f);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3){
    perror("Usage: count_values <fileWithKVs> <fileWithNames1> [fileWithNames2 ...]\n");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    perror("Could not generate key/value pairs from file");
  }
 //count from 2 to argc (call the number you count i)
  for (int i = 0; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      printf("Error writing the results.\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);

  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
