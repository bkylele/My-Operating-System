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

void terminal_init(struct Terminal *term, Multiboot * m);
uint32* pixelAt(struct Terminal *term, uint16 x, uint16 y);
void drawHorizontalLine(struct Terminal *term);


#endif
