#include "terminal.h"
#include <multiboot.h>
#include <vga.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


void kernel_main([[maybe_unused]] unsigned long magic, unsigned long addr) {
    multiboot_info_t *mbi = (multiboot_info_t *) addr;
    terminal_init(mbi);

    terminal_write("Hello World!", 12);
}
