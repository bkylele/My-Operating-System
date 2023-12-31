GPPPARAMS = -m32 -nostdlib -fno-stack-protector -fno-builtin -fno-exceptions -fno-leading-underscore -I.
ASPARAMS = --32
LDPARAMS = -melf_i386

SRCS := $(wildcard *.c */*.c */*/*.c */*/*/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

ASMSRCS := $(wildcard *.s */*.s */*/*.s */*/*/*.s)
ASMOBJS := $(patsubst %.s,%.o,$(ASMSRCS))

# objects = boot.o kernel.o

%.o: %.c
	gcc $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

myos.bin:  linker.ld $(OBJS) $(ASMOBJS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJS) $(ASMOBJS) font.o

install: myos.bin
	sudo cp $< /boot/myos.bin

myos.iso: myos.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/myos.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: myos.iso
	(killall VirtualBox && sleep 1) || true
	virtualboxvm --startvm "My Operating System" &

clean:
	rm -f myos.bin $(OBJS) $(ASMOBJS) myos.bin
