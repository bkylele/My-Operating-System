#include "drivers/terminal.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void kernel_main(unsigned long magic, unsigned long * addr) {
    Multiboot *mbi = (Multiboot *) addr;
    terminalInit(mbi);

    terminalWrite("Back to where I started!", 24);
}
