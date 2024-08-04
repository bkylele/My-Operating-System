#ifndef TERMINAL_H
#define TERMINAL_H

#include <multiboot.h>
#include <stddef.h>

void terminal_init(multiboot_info_t *mbi);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t n);



#endif
