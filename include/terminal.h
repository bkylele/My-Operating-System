#ifndef TERMINAL_H
#define TERMINAL_H

#include <multiboot.h>
#include <stddef.h>

void terminal_init(multiboot_info_t *mbi);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

void terminal_writedec(size_t num);
void terminal_writehex(size_t num);

void terminal_clear();
void terminal_clear_row(size_t y);
void terminal_scroll();



#endif
