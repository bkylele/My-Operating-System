#include <stdint.h>
#include <vga.h>
#include <terminal.h>


const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

size_t terminal_column;
size_t terminal_row;
color_info_t terminal_fg_color;
color_info_t terminal_bg_color;


void terminal_init(multiboot_info_t *mbi) {
    vga_init(mbi);

    terminal_column = 0;
    terminal_row = 0;
    terminal_fg_color = (color_info_t){ {255, 255, 255} };
    terminal_bg_color = (color_info_t){ {0, 0, 0} };        
}


void terminal_putchar(char c) {
    draw_char(c, terminal_column, terminal_row,
            terminal_fg_color.data,
            terminal_bg_color.data);

    if (++terminal_column > VGA_WIDTH) {
        terminal_column = 0;
        ++terminal_row;
    }
}


void terminal_write(const char* data, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        terminal_putchar(data[i]);
    }
}

