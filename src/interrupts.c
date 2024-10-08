
#include <interrupts.h>
#include <terminal.h>
#include <io.h>


__attribute__((aligned(0x10)))
idt_entry_t idt_entries[256];

idtr_t _idtr_ptr;

extern void _idt_flush();

extern void _interrupt_ignore();

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();


void idt_set_descriptor(uint8_t vec_index, void* isr, uint8_t flags) {
    idt_entries[vec_index].offset_lo      = (uint32_t)isr & 0xFFFF;
    idt_entries[vec_index].offset_hi      = (uint32_t)isr >> 16;

    idt_entries[vec_index].kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    idt_entries[vec_index].attributes     = flags;
    idt_entries[vec_index].reserved       = 0;
}


uint32_t _irq_handler(uint8_t interrupt_num, uint32_t esp) {
    if (interrupt_num == 0x21) {
        unsigned char in = inb(0x60);
        terminal_writedec(in);
        terminal_writestring(" ");
    }
    outb(0x20, 0x20);
    if (interrupt_num >= 0x28 && interrupt_num <= 0x30) {
        outb(0xA0, 0x20);
    }
    return esp;
}


void idt_init() {
    terminal_writestring("Initializing Interrupt Descriptor Table...\n");

    // Setup intel's 32 reserved exceptions (0-31)
    int i;
    for (i = 0; i < 256; ++i) {
        idt_set_descriptor(i, &_interrupt_ignore, 0x8E);
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

    _idtr_ptr.base = (uint32_t)idt_entries;
    _idtr_ptr.limit = sizeof(idt_entries) - 1;
    _idt_flush();
}
