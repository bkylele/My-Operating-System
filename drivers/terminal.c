#include "../drivers/terminal.h"

void terminal_init(struct Terminal *term, Multiboot *m) {
    term->framebuffer = (uint32 *) m->framebuffer_addr;
    term->height = m->framebuffer_height;
    term->width = m->framebuffer_width;
    term->pitch = m->framebuffer_pitch;
    term->bits_per_pixel = m->framebuffer_bpp;
}

uint32* pixelAt(struct Terminal *term, uint16 x, uint16 y) {
    return (uint32 *)(term->framebuffer + (y*term->pitch + x*(term->bits_per_pixel/8)));
}

void drawHorizontalLine(struct Terminal *term) {
    unsigned i;
    for (i=0; i<term->width; ++i) {
        uint32 *pixel = pixelAt(term, i, term->height / 2);
        *pixel = 0x0000FF;
    }
}

