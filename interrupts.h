#ifndef __MYOS__INTERRUPTS_H
#define __MYOS__INTERRUPTS_H

#include <stdint.h>


struct idt_entry {
	uint16_t    offset_lo;    // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    offset_hi;    // The higher 16 bits of the ISR's address
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;


struct idtr {
    uint16_t    limit;
    uint32_t    base;
}__attribute__((packed));
typedef struct idtr idtr_t;


void idt_set_descriptor(uint8_t vec_index, void* isr, uint8_t flags);
void idt_init();
uint32_t _irq_handler(uint8_t interrupt_num, uint32_t esp);


#endif /* ifndef __MYOS__INTERRUPTS_H */
