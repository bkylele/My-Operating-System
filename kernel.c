#include "drivers/terminal.h"
#include "multiboot/multiboot2.h"
#include <sys/types.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void kernel_main(unsigned long magic, unsigned long * addr) {
    Multiboot *mbi = (Multiboot *) addr;

    struct Terminal term;
    terminal_init(&term, mbi);

    /* putstr(&term, 0, 0, "Hello World!", 0xFFFFFF); */
    /* drawHorizontalLine(&term); */
    /* drawRectangle(&term, 0, 0, 255, 500, 800); */

}
