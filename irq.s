
.section .text

.extern _irq_handler

.global _irq0
_irq0:
    movb $0x20, [interrupt_num]
    jmp irq_common_stub


.global _irq1
_irq1:
    movb $0x21, [interrupt_num]
    jmp irq_common_stub



irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    pushl %esp
    push [interrupt_num]
    call _irq_handler
    mov %eax, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

.global _interrupt_ignore
_interrupt_ignore:

    iret



.data
    interrupt_num: .byte 0
