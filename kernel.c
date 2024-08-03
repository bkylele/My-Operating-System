#include <multiboot.h>
#include <vga.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


void kernel_main([[maybe_unused]] unsigned long magic, unsigned long addr) {
    multiboot_info_t *mbi = (multiboot_info_t *) addr;

    vga_init(mbi);
    draw_diagonal_line(0);
    draw_horizontal_line(100);
    draw_vertical_line(100);

}
