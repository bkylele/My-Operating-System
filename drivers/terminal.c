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

void putpixel(struct Terminal *term, uint16 x, uint16 y, uint32 color) {
    *pixelAt(term, x, y) = color;
}

void drawHorizontalLine(struct Terminal *term) {
    unsigned i;
    for (i=0; i<term->width; ++i) {
        uint32 *pixel = pixelAt(term, i, term->height / 2);
        *pixel = 0x0000FF;
    }
}

void drawRectangle(struct Terminal *term, uint8 r, uint8 g, uint8 b,
        uint8 width, uint8 height) {
    unsigned char* pixel = term->framebuffer;
    int i,j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            pixel[j*term->bits_per_pixel / 8] = b;
            pixel[j*term->bits_per_pixel / 8 + 1] = g;
            pixel[j*term->bits_per_pixel / 8 + 2] = r;
        }
        pixel+=term->pitch;
    }
}

void putchar(struct Terminal *term, PSF_font *font, uint16 x, uint16 y, char c, uint32 color) {
    uint8 *offset = (uint8 *) &_binary_cp866_8x16_psf_start + font->headersize;  // offset of the bitmaps
    uint8 *glyph = offset + (uint8)c * font->bytesperglyph;

    uint8 i, j;

    for (i = 0; i < font->height; ++i) {
        uint8 rowData = glyph[i];
        for (j = 0; j < font->width; ++j) {
            if (rowData & (1 << (font->width - j - 1))) {
                putpixel(term, x+j, y+i, color);
            }
        }
    }
}

void putstr(struct Terminal *term, uint16 x, uint16 y, const char* s, uint32 color) {
    PSF_font *font = (PSF_font *) &_binary_cp866_8x16_psf_start;
    uint16 col = 0;
    while (*s != '\0') {
        putchar(term, font, x+col, y, *s, color);
        col += font->width;
        ++s;
    }
}
