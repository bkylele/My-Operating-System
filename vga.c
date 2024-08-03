#include <vga.h>

uint32_t fb_addr;
uint32_t fb_pitch;
uint32_t fb_width;
uint32_t fb_height;
uint8_t fb_bits_per_pixel;

uint8_t fb_r_position;    /* field position */
uint8_t fb_r_size;        /* mask size */
uint8_t fb_g_position;
uint8_t fb_g_size;
uint8_t fb_b_position;
uint8_t fb_b_size;

/*
 * As of now, I'm not too sure how important it is to support the other color
 * information types, so I'll come back to it later.
 */
uint32_t color;


void vga_init(const multiboot_info_t *mbi) {
    fb_addr             = mbi->framebuffer_addr;
    fb_pitch            = mbi->framebuffer_pitch;
    fb_width            = mbi->framebuffer_width;
    fb_height           = mbi->framebuffer_height;
    fb_bits_per_pixel   = mbi->framebuffer_bpp;

    fb_r_position       = mbi->framebuffer_red_field_position;
    fb_r_size           = mbi->framebuffer_red_mask_size;
    fb_g_position       = mbi->framebuffer_green_field_position;
    fb_g_size           = mbi->framebuffer_green_mask_size;
    fb_b_position       = mbi->framebuffer_blue_field_position;
    fb_b_size           = mbi->framebuffer_blue_mask_size;

    set_color(255, 255, 255); // default color white
}


void set_color(uint8_t r, uint8_t g, uint8_t b) {
    // for now, assuming 24-bit rgb info

    color |= (r << fb_r_position);
    color |= (g << fb_g_position);
    color |= (b << fb_b_position);
}


void putpixel(size_t x, size_t y) {
    // for now, assuming 32 bits per pixel
    uint32_t *pixel = (uint8_t *) fb_addr + (fb_pitch * y) + (fb_bits_per_pixel / 8) * x;
    *pixel = color;
}


void draw_diagonal_line(bool pos) {
    if (pos) {
        for (int i = 0; i < (int)fb_width && i < (int)fb_height; i++) {
            putpixel(i, i);
        }
    } else {
        for (int i = 0; i < (int)fb_width && i < (int)fb_height; i++) {
            putpixel(-i, i);
        }
    }
}

void draw_horizontal_line(size_t y) {
    for (int i = 0; i < (int)fb_width; ++i) {
        putpixel(i, y);
    }
}

void draw_vertical_line(size_t x) {
    for (int i = 0; i < (int)fb_height; ++i) {
        putpixel(x, i);
    }
}
