AS = ~/opt/cross/bin/i686-elf-as
CC = ~/opt/cross/bin/i686-elf-gcc

CCPARAMS = -I. -ffreestanding -O2 -Wall
ASPARAMS = --32
LDPARAMS = -melf_i386

SRCS := $(wildcard *.c)
ASMSRCS := $(wildcard *.s)
FONTSRCS := $(wildcard *.psf)

OBJS := $(patsubst %.c, build/%.o, $(SRCS)) $(patsubst %.s, build/%.o, $(ASMSRCS)) $(patsubst %.psf, build/%.o, $(FONTSRCS))

BUILDDIR := build
BINDIR := bin

default: $(BINDIR)/myos.bin

$(BUILDDIR)/%.o: %.c
	$(CC) $(CCPARAMS) $< -o $@ -c

$(BUILDDIR)/%.o: %.s
	$(AS) $< -o $@

$(BUILDDIR)/%.o: %.psf
	objcopy -O elf32-i386 -B i386 -I binary $< $@

$(BINDIR)/myos.bin: linker.ld setup $(OBJS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJS)

# install: myos.bin
# 	sudo cp $< /boot/myos.bin

$(BINDIR)/myos.iso: $(BINDIR)/myos.bin
	mkdir -p iso/boot/grub
	cp $< iso/boot/
	echo 'menuentry "myos" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: $(BINDIR)/myos.iso
	qemu-system-i386 -cdrom $<

setup:
	mkdir -p $(BINDIR)
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BINDIR) $(BUILDDIR)


.PHONY: setup clean
