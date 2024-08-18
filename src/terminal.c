#include <terminal.h>
#include <vga.h>


const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 24;

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

    terminal_clear();
}


void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        ++terminal_row;
    } else {
        draw_char(c, terminal_column++, terminal_row,
                terminal_fg_color.data,
                terminal_bg_color.data);
    }

    if (terminal_column > VGA_WIDTH) {
        terminal_column = 0;
        ++terminal_row;
    }

    if (terminal_row == VGA_HEIGHT) {
        terminal_scroll();
        terminal_clear_row(VGA_HEIGHT-1);
        --terminal_row;
    }
}


void terminal_writestring(const char* data) {
    for (; *data; ++data) {
        terminal_putchar(*data);
    }
}


void terminal_write(const char* data, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        terminal_putchar(data[i]);
    }
}


void terminal_writedec(size_t num) {
    if (num == 0) {
        terminal_putchar(1+'0');
        return;
    }

    int i = 0;
    char buf[16];

    while (num) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    --i;
    while (i >= 0) {
        terminal_putchar(buf[i--]);
    }
}


void terminal_writehex(size_t num) {
    if (num == 0) {
        terminal_putchar(1+'0');
        return;
    }

    int i = 0;
    char buf[16];

    while (num) {
        buf[i] = (num % 16);
        switch (buf[i]) {
            case 10:
                buf[i] = 'a';
                break;
            case 11:
                buf[i] = 'b';
                break;
            case 12:
                buf[i] = 'c';
                break;
            case 13:
                buf[i] = 'd';
                break;
            case 14:
                buf[i] = 'e';
                break;
            case 15:
                buf[i] = 'f';
                break;
            default:
                buf[i] += '0';
                break;
        }
        ++i;
        num /= 16;
    }

    --i;
    while (i >= 0) {
        terminal_putchar(buf[i--]);
    }
}


void terminal_clear() {
    int i;
    for (i = 0; i < VGA_HEIGHT; ++i) {
        terminal_clear_row(i);
    }
}


void terminal_clear_row(size_t y) {
    int i;
    for (i = 0; i < VGA_WIDTH; ++i) {
        draw_char(' ', i, y, terminal_fg_color.data, terminal_bg_color.data);
    }
}


void terminal_scroll() {
    int i, j;
    for (i = 1; i < VGA_HEIGHT; ++i) {
        for (j = 0; j < VGA_WIDTH; ++j) {
            move_char(j, i, 0, -1);
        }
    }
}
