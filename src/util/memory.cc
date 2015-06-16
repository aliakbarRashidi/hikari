#include <stdio.h>
#include <stdlib.h>
#include "memory.hh"

void* checked_malloc(size_t size) {
  void* ret = malloc(size); 
  return check(ret);
}

void* checked_realloc(void* orig, size_t size) {
  void* ret = realloc(orig, size); 
  return check(ret);
}

void* check(void* ptr) {
  if(ptr == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
