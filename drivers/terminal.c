#include "terminal.h"

void terminalInit(Multiboot *m) {
    PSF_font *font_info = (PSF_font *) &_binary_cp866_8x16_psf_start;

    vbeInit(m);
    framebuffer_width = m->framebuffer_width / font_info->width;
    framebuffer_height = m->framebuffer_height / font_info->height;
    terminal_framebuffer = (uint32 *) m->framebuffer_addr;
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = 0xFFFFFF;
}

void terminalSetColor(uint32 color) {
    terminal_color = color;
}

void terminalPutChar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        ++terminal_row;
    }
    putchar(terminal_column, terminal_row, c, terminal_color);
    if (++terminal_column == framebuffer_width) {
        terminal_column = 0;
        ++terminal_row;
    }
}

void terminalWrite(const char* s, siz size) {
    for (uint64 i = 0; i < size; ++i)
        terminalPutChar(s[i]);
}
