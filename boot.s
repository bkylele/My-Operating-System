.set ALIGN,     1<<0 
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1badb002
.set CHECKSUM,  -(MAGIC + FLAGS)


.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# aout kludge (unused)
.long 0,0,0,0,0

# Video mode flags
.long   0   # Linear graphics
.long   0   # Preferred width
.long   0   # Preferred height
.long   0   # Preferred pixel depth


.section .bss
.align 16
stack_bot:
.space 2*1024*1024
stack_top:


.section .text
.global _start
.type _start, @function

_start:
    mov $stack_top, %esp
    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start ,. - _start
