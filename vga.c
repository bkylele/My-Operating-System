#include <vga.h>
#include <font.h>

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
}


uint32_t *pixel_at(size_t x, size_t y) {
    // for now, assuming 32 bits per pixel
    return (uint32_t *) ((uint8_t *) fb_addr + (fb_pitch * y) + (fb_bits_per_pixel / 8) * x);
}


void put_pixel(size_t x, size_t y, uint32_t color) {
    *pixel_at(x,y) = color;
}


void move_pixel(size_t x, size_t y, size_t new_x, size_t new_y) {
    *pixel_at(new_x, new_y) = *pixel_at(x,y);
}


// why is this a char???
extern char _binary_lat9_16_psf_start;

void draw_char(unsigned char c, size_t cx, size_t cy, uint32_t fgcolor, uint32_t bgcolor) {
    PSF_font *font = (PSF_font *) &_binary_lat9_16_psf_start;

    unsigned char* glyph = (uint8_t*) font + font->headersize
        + (c>0 && c<font->numglyph ? c : 0) * font->bytesperglyph;

    size_t offx = cx * font->width;
    size_t offy = cy * font->height;

    unsigned char x, y, mask;
    for (y = 0; y < font->height; ++y) {
        mask = 1 << (font->width - 1); // left-side of the line, little-endian

        for (x = 0; x < font->width; ++x) {
            put_pixel(offx + x, offy + y, *glyph & mask ? fgcolor : bgcolor);
            mask >>= 1;
        }

        ++glyph;
    }
    
}


void move_char(size_t cx, size_t cy, int dcx, int dcy) {
    PSF_font *font = (PSF_font *) &_binary_lat9_16_psf_start;

    size_t offx = cx * font->width;
    size_t offy = cy * font->height;
    size_t new_offx = (cx + dcx) * font->width;
    size_t new_offy = (cy + dcy) * font->height;

    int x, y;
    for (y = 0; y < font->height; ++y) {
        for (x = 0; x < font->width; ++x) {
            move_pixel(offx+x, offy+y, new_offx+x, new_offy+y);
        }
    }
}


void draw_diagonal_line(bool pos, uint32_t color) {
    if (pos) {
        for (int i = 0; i < fb_width && i < fb_height; i++) {
            put_pixel(i, i, color);
        }
    } else {
        for (int i = 0; i < fb_width && i < fb_height; i++) {
            put_pixel(-i, i, color);
        }
    }
}

void draw_horizontal_line(size_t y, uint32_t color) {
    for (int i = 0; i < fb_width; ++i) {
        put_pixel(i, y, color);
    }
}

void draw_vertical_line(size_t x, uint32_t color) {
    for (int i = 0; i < fb_height; ++i) {
        put_pixel(x, i, color);
    }
}
