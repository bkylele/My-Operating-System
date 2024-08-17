#ifndef __MYOS__GDT_H
#define __MYOS__GDT_H

#include <stdint.h>

struct gdt_entry {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_hi;
    uint8_t base_hi;
}__attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

void gdt_init();
void gdt_set_gate(gdt_entry_t *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);


#endif /* ifndef __MYOS__GDT_H */
