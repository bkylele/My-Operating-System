#include "terminal.h"
#include <multiboot.h>
#include <vga.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


void kernel_main([[maybe_unused]] unsigned long magic, unsigned long addr) {
    multiboot_info_t *mbi = (multiboot_info_t *) addr;
    terminal_init(mbi);

    const char str[] = "Lorem ipsum dolor sit amet, consetetur sadipscing"
        "elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna"
        "aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo"
        "dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus"
        "est Lorem ipsum dolor sit amet.";
    terminal_write(str, sizeof(str) - 1);

}
