AS = ~/opt/cross/bin/i686-elf-as
CC = ~/opt/cross/bin/i686-elf-gcc

CCPARAMS = -I. -ffreestanding -O2 -Wall
ASPARAMS = --32
LDPARAMS = -melf_i386

SRCS := $(wildcard *.c */*.c */*/*.c */*/*/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

ASMSRCS := $(wildcard *.s */*.s */*/*.s */*/*/*.s)
ASMOBJS := $(patsubst %.s,%.o,$(ASMSRCS))

FONTSRCS := $(wildcard *.psf)
FONTOBJS := $(patsubst %.psf,%.o,$(FONTSRCS))


%.o: %.c
	$(CC) $(CCPARAMS) $< -o $@ -c

%.o: %.s
	$(AS) $< -o $@

%.o: %.psf
	objcopy -O elf32-i386 -B i386 -I binary $< $@

myos.bin:  linker.ld $(OBJS) $(ASMOBJS) $(FONTOBJS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJS) $(ASMOBJS) $(FONTOBJS)

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
	rm -f myos.bin $(OBJS) $(ASMOBJS) $(FONTOBJS) myos.iso
