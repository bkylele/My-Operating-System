#ifndef __MYOS__GDT_H
#define __MYOS__GDT_H


#include <stdint.h>

struct segment_descriptor {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_hi;
    uint8_t base_hi;
};

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));;

void gdt_init();
void gdt_set_gate(struct segment_descriptor *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);


#endif /* ifndef __MYOS__GDT_H */
