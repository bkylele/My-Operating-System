#ifndef __MYOS__VGA_H
#define __MYOS__VGA_H

#include <multiboot.h>
#include <stdint.h>
#include <stddef.h>

void vga_init(const multiboot_info_t *mbi);
void set_color(uint8_t r, uint8_t g, uint8_t b);
void putpixel(size_t x, size_t y);

void draw_diagonal_line(bool pos);
void draw_horizontal_line(size_t y);
void draw_vertical_line(size_t x);


#endif /* ifndef __MYOS__VGA_H */
