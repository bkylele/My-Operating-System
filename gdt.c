
#include <gdt.h>

enum {
    SEG_NULL,
    SEG_KERNEL_CODE,
    SEG_KERNEL_DATA,
    SEG_USER_CODE,
    SEG_USER_DATA,
    SEG_TASK_STATE,
};
struct segment_descriptor gdt_entries[6];
struct gdt_ptr gdt_p;

extern void gdt_flush();

void gdt_set_gate(struct segment_descriptor *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    // Setup base
    entry->base_lo  = base & 0xFFFF;
    entry->base_mid = (base >> 16) & 0xFF;
    entry->base_hi  = (base >> 24) & 0xFF;

    // Setup limit
    entry->limit_lo = limit & 0xFFFF;
    entry->limit_hi = (limit >> 16) & 0x0F;

    // Setup access byte
    entry->access = access;

    // Setup flags
    entry->limit_hi |= (flags << 4);
}


void gdt_init() {
    gdt_p.limit = sizeof(gdt_entries) - 1;
    gdt_p.base = (uint32_t) &gdt_entries;

    // NULL segment
    gdt_set_gate(&gdt_entries[SEG_NULL], 0, 0, 0, 0);

    // Kernel segments
    gdt_set_gate(&gdt_entries[SEG_KERNEL_CODE], 0, 0xFFFFF, 0x9A, 0xC);
    gdt_set_gate(&gdt_entries[SEG_KERNEL_DATA], 0, 0xFFFFF, 0x92, 0xC);

    // User segments
    gdt_set_gate(&gdt_entries[SEG_USER_CODE], 0, 0xFFFFF, 0xFA, 0xC);
    gdt_set_gate(&gdt_entries[SEG_USER_DATA], 0, 0xFFFFF, 0xF2, 0xC);

    // Task state segment
    gdt_set_gate(&gdt_entries[SEG_TASK_STATE], 0, 0, 0, 0);

    gdt_flush();
}

