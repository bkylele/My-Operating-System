.set ALIGN,         1<<0 
.set MEMINFO,       1<<1
.set VIDEO,         1<<2
.set FLAGS,     ALIGN | MEMINFO | VIDEO
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
.long   32   # Preferred pixel depth


.section .bss
.align 16
stack_bot:
.skip 16*1024 # 16 Kib
stack_top:


.section .text
.global _start
.type _start, @function

_start:
    # Initialize stack pointer
    mov $stack_top, %esp

    # Pushing pointer to multiboot information structure
    pushl %ebx
    # Pushing magic value
    pushl %eax

    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start ,. - _start
