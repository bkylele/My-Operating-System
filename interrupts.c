
#include <interrupts.h>
#include <terminal.h>
#include <io.h>


__attribute__((aligned(0x10)))
idt_entry_t idt_entries[256];

idtr_t _idtr_ptr;

extern void _idt_flush();

extern void _irq0();
extern void _irq1();


void idt_set_descriptor(uint8_t vec_index, void* isr, uint8_t flags) {
    idt_entries[vec_index].offset_lo      = (uint32_t)isr & 0xFFFF;
    idt_entries[vec_index].offset_hi      = (uint32_t)isr >> 16;

    idt_entries[vec_index].kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    idt_entries[vec_index].attributes     = flags;
    idt_entries[vec_index].reserved       = 0;
}


uint32_t _irq_handler(uint8_t interrupt_num, uint32_t esp) {
    terminal_write("INTERRUPT", 9);
    return esp;
}



void idt_init() {
    _idtr_ptr.base = (uint32_t)idt_entries;
    _idtr_ptr.limit = sizeof(idt_entries) - 1;
    // Setup intel's 32 reserved exceptions (0-31)
    int i;
    for (i = 0; i < 256; ++i) {
        idt_set_descriptor(i, &_irq0, 0x8E);
    }

    // Setup 16 IRQs after the exception numbers (32-47)
    idt_set_descriptor(0x20, &_irq0, 0x8E);
    idt_set_descriptor(0x21, &_irq1, 0x8E);
    // idt_set_descriptor(0x22, NULL, 0x8E);
    // idt_set_descriptor(0x23, NULL, 0x8E);
    // idt_set_descriptor(0x24, NULL, 0x8E);
    // idt_set_descriptor(0x25, NULL, 0x8E);
    // idt_set_descriptor(0x26, NULL, 0x8E);
    // idt_set_descriptor(0x27, NULL, 0x8E);
    // idt_set_descriptor(0x28, NULL, 0x8E);
    // idt_set_descriptor(0x29, NULL, 0x8E);
    // idt_set_descriptor(0x2a, NULL, 0x8E);
    // idt_set_descriptor(0x2b, NULL, 0x8E);
    // idt_set_descriptor(0x2c, NULL, 0x8E);
    // idt_set_descriptor(0x2d, NULL, 0x8E);
    // idt_set_descriptor(0x2e, NULL, 0x8E);
    // idt_set_descriptor(0x2f, NULL, 0x8E);


    // Setup to initialize the primary PIC. Send ICW 1
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // ICW 2 - Map IRQ base interrupt numbers
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // ICW 3 - Set the IR line to connect both PICs ---------
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // Send ICW 4 - Set x86 mode
    outb(0x21, 0x01); // bit 0 enables 80x86 mode
    outb(0xA1, 0x01);

    // All done. Null out the data registers
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    _idt_flush();
}
