#include <string.h>

void *memcpy(void *destination, const void *source, size_t num) {
    char *dest = destination;
    const char *src = source;
    for (int i = 0; i < num; ++i) {
        dest[i] = src[i];
    }
    return destination;
}

void* memset(void *ptr, int value, size_t num) {
    char *p = ptr;
    for (int i = 0; i < num; ++i) {
        p[i] = (unsigned char) value;
    }
    return ptr;
}


char *strcpy(char *destination, const char *source) {
    return 0;
}

char *strncpy(char *destination, const char *source, size_t num) {
    return 0;
}

size_t strlen(const char* str) {
    return 0;
}

