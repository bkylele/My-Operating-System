#ifndef _STRING_H
#define _STRING_H 

#include <stddef.h>

void *memcpy(void *destination, const void *source, size_t num);
void* memset(void *ptr, int value, size_t num);

char *strcpy(char *destination, const char *source);
char *strncpy(char *destination, const char *source, size_t num);
size_t strlen(const char*);


#endif
