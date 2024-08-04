#include <multiboot.h>
#include <vga.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))


void kernel_main([[maybe_unused]] unsigned long magic, unsigned long addr) {
    multiboot_info_t *mbi = (multiboot_info_t *) addr;

    vga_init(mbi);

    color_info_t color1 = { {255, 255, 255} };
    color_info_t color2 = { {0, 0, 0} };

    draw_char('A', 0, 0, color1.data, color2.data);
    draw_char('B', 1, 0, color1.data, color2.data);
    draw_char('C', 0, 1, color1.data, color2.data);

    // draw_diagonal_line(1, color1.data);
    // draw_horizontal_line(100, color.data);
    // draw_vertical_line(100, color.data);

}
