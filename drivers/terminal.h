#ifndef TERMINAL_H
#define TERMINAL_H

#include "vbe.h"

static siz framebuffer_width;  // in terms of characters
static siz framebuffer_height;

static uint32* terminal_framebuffer;
static uint32 terminal_row;   
static uint32 terminal_column;
static uint32 terminal_color;

void terminalInit(Multiboot *m);
void terminalSetColor(uint32 color);
void terminalPutChar(char c);
void terminalWrite(const char* s, siz size);

#endif
