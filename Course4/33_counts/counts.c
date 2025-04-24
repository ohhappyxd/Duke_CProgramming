#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->counts = NULL;
  counts->size = 0;
  counts->numUnknown = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->numUnknown++;
    return;
  }
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(name, c->counts[i]->value) == 0) {
      c->counts[i]->count++;
      return;
    }
  }
  // Add new entry
  one_count_t * newEntry = malloc(sizeof(*newEntry));
  if (newEntry == NULL) {
    return;
  }
  newEntry->value = strdup(name);
  if (newEntry->value == NULL) {
    free(newEntry);
    return;
  }
  newEntry->count = 1;
  one_count_t ** newCounts = realloc(c->counts, (c->size + 1) * sizeof(*c->counts));
  if (newCounts == NULL) {
    free(newEntry->value);
    free(newEntry);
    return;
  }
  
  c->counts = newCounts;
  c->counts[c->size] = newEntry;
  c->size++;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %zu\n", c->counts[i]->value, c->counts[i]->count);
  }
  if (c->numUnknown > 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->numUnknown);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    if (c->counts[i] != NULL) {
      free(c->counts[i]->value);
      free(c->counts[i]);
    }
  }
  free(c->counts);
  free(c);
}
