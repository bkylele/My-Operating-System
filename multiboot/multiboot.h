#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>
#include <stddef.h>

typedef unsigned char              uint8;
typedef unsigned short             uint16;
typedef unsigned int               uint32;
typedef unsigned long long         uint64;

typedef size_t  siz;

struct MultibootInfo {
    uint32 flags;

    uint32 mem_lower;
    uint32 mem_upper;

    uint32 boot_device;

    uint32 cmdline;

    uint32 mods_count;
    uint32 mods_addr;

    uint32 num;
    uint32 size;
    uint32 addr;
    uint32 shndx;

    uint32 mmap_len;
    uint32 mmap_addr;

    uint32 drives_len;
    uint32 drives_addr;

    uint32 config_table;

    uint32 boot_loader_name;

    uint32 apm_table;

    uint32 vbe_control_info;
    uint32 vbe_mode_info;
    uint16 vbe_mode;
    uint16 vbe_interface_seg;
    uint16 vbe_interface_off;
    uint16 vbe_interface_len;

    uint64 framebuffer_addr;
    uint32 framebuffer_pitch;
    uint32 framebuffer_width;
    uint32 framebuffer_height;
    uint8 framebuffer_bpp;
    uint8 framebuffer_type;

    union {
        struct {
            uint32 palette_addr;
            uint16 palette_num_color;
        };
        struct {
            uint8 red_field_position;
            uint8 red_mask_size;
            uint8 green_field_position;
            uint8 green_mask_size;
            uint8 blue_field_position;
            uint8 blue_mask_size;
        };
    };
}__attribute__((packed));

typedef struct MultibootInfo Multiboot;

#endif
