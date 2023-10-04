#ifndef TERMINAL_H
#define TERMINAL_H

#include "../multiboot/multiboot2.h"

struct Terminal {
    void * framebuffer;
    uint32 height;
    uint32 width;
    uint32 pitch; 
    uint8  bits_per_pixel;
};

typedef struct {
    uint32 magic;         /* magic bytes to identify PSF */
    uint32 version;       /* zero */
    uint32 headersize;    /* offset of bitmaps in file, 32 */
    uint32 flags;         /* 0 if there's no unicode table */
    uint32 length;        /* number of glyphs */
    uint32 bytesperglyph; /* size of each glyph */
    uint32 height;        /* height in pixels */
    uint32 width;         /* width in pixels */
} PSF_font;

extern char _binary_cp866_8x16_psf_start;
extern char _binary_cp866_8x16_psf_end;
extern char _binary_cp866_8x16_psf_size;

void terminal_init(struct Terminal *term, Multiboot * m);
uint32* pixelAt(struct Terminal *term, uint16 x, uint16 y);
void putpixel(struct Terminal *term, uint16 x, uint16 y, uint32 color);
void drawHorizontalLine(struct Terminal *term);
void drawRectangle(struct Terminal *term, uint8 r, uint8 g, uint8 b,
        uint8 width, uint8 height);

void putchar(struct Terminal *term, PSF_font *font, uint16 x, uint16 y, char c,
             uint32 color);
void putstr(struct Terminal *term, uint16 x, uint16 y, const char *s,
            uint32 color);

#endif
