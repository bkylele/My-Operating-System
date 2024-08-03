AS = ~/opt/cross/bin/i686-elf-as
CC = ~/opt/cross/bin/i686-elf-gcc

CCPARAMS = -I. -I./include -I./multiboot -ffreestanding -O2 -Wall -Wextra
ASPARAMS = --32
LDPARAMS = -melf_i386

SRCS := $(wildcard *.c */*.c */*/*.c */*/*/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

ASMSRCS := $(wildcard *.s */*.s */*/*.s */*/*/*.s)
ASMOBJS := $(patsubst %.s,%.o,$(ASMSRCS))

# objects = boot.o kernel.o

%.o: %.c
	$(CC) $(CCPARAMS) $< -o $@ -c

%.o: %.s
	$(AS) $< -o $@

myos.bin:  linker.ld $(OBJS) $(ASMOBJS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJS) $(ASMOBJS) # font.o

install: myos.bin
	sudo cp $< /boot/myos.bin

myos.iso: myos.bin
	mkdir -p iso/boot/grub
	cp $< iso/boot/
	echo 'menuentry "myos" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: myos.iso
	qemu-system-i386 -cdrom $<

clean:
	rm -f myos.bin $(OBJS) $(ASMOBJS) myos.iso
