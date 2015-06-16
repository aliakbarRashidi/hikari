#ifndef UTIL_MEMORY_H
#define UTIL_MEMORY_H

void* checked_malloc(size_t size); 
void* checked_realloc(void* orig, size_t size); 
void* check(void* ptr);

#endif // UTIL_MEMORY_H
