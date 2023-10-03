#include "drivers/terminal.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void kernel_main(unsigned long magic, unsigned long * addr) {
    Multiboot *mbi = (Multiboot *) addr;
    struct Terminal term;

    terminal_init(&term, mbi);
    drawHorizontalLine(&term);
}
