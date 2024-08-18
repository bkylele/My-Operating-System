AS = ~/opt/cross/bin/i686-elf-as
CC = ~/opt/cross/bin/i686-elf-gcc

CCFLAGS = -I. -Iinclude -Ilibc/include -ffreestanding -O2 -Wall -libc
ASFLAGS = --32
LDFLAGS = -melf_i386

BUILDDIR := build
BINDIR := bin

CSRCS := $(shell find src/ -name *.c)
ASMSRCS := $(shell find src/ -name *.s)
FONTS := $(shell find src/ -name *.psf)

LIBC := $(shell find libc/src/ -name *.c)
LIBCDEP := $(LIBC:libc/src/%.c=build%.d)

DEP := $(CSRCS:src/%.c=build/%.d) $(LIBCDEP)
OBJS := $(CSRCS:src/%.c=build/%.o) $(ASMSRCS:src/%.s=build/%.o) \
	$(FONTS:src/%.psf=build/%.o) $(LIBC:libc/src/%.c=build/%.o)


# test:
# 	@echo $(LIBC)

myos.bin: linker.ld $(OBJS)
	@mkdir -p $(BINDIR)
	ld $(LDFLAGS) -T $< -o bin/$@ $(OBJS)

myos.iso: myos.bin
	mkdir -p iso/boot/grub
	cp $(BINDIR)/$< iso/boot/
	echo 'menuentry "myos" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(BINDIR)/$@ iso
	rm -rf iso



$(BUILDDIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@

$(BUILDDIR)/%.o: src/%.s
	@mkdir -p $(@D)
	$(AS) $< -o $@

$(BUILDDIR)/%.o: src/%.psf
	@mkdir -p $(@D)
	objcopy -O elf32-i386 -B i386 -I binary $< $@

$(BUILDDIR)/%.o: libc/src/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -MMD -MP -c $< -o $@


-include $(DEP)



qemu: myos.iso
	qemu-system-i386 -cdrom $(BINDIR)/$<

clean:
	rm -rf $(BINDIR) $(BUILDDIR)


.PHONY: clean, qemu
