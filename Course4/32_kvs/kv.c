#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void trimNewline(char * str) {
  char * newline = strchr(str, '\n');
  if (newline) {
    * newline = '\0';
  }
}

kvpair_t * parseline(char * line) {
  const char * equal = strchr(line, '=');
  if (equal == NULL) {
    return NULL;
  }
  size_t keyLen = equal - line;
  char * key = strndup(line, keyLen);
  char * value = strdup(equal + 1);
  trimNewline(value);
  
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = key;
  pair->value = value;
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * kvs = malloc(sizeof(*kvs));
  kvs->pairs = NULL;
  kvs->numPairs = 0;
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) != -1) {
    kvpair_t * pair = parseline(line);
    if (pair) {
      kvs->pairs = realloc(kvs->pairs, (kvs->numPairs + 1) * sizeof(*kvs->pairs));
      kvs->pairs[kvs->numPairs] = pair;
      kvs->numPairs++;
    }
  }
  free(line);
  fclose(f);
  return kvs;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]->value);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i]->key, pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->numPairs; i++) {
    if (strcmp(pairs->pairs[i]->key, key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
