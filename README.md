# MinimalOS
---------------------
An exploratory project on implementing a 32-bit operating system.

# Requirements
Requires i386-elf-binutils for compilation (gcc, make). Requires
VirtualBox, grub-legacy, and xorriso for virtualization.

# Roadmap

- [x] Basic printing
- [x] Drawing in the linear framebuffer
- [ ] Global Descriptor Table
- [ ] Interrupt Descriptor Table

# Building

``` bash
$ make run clean # this will run VirtualBox
```
To install kernel to grub bootloader, do

``` bash
$ make install
```
NOTE: As of now you need to manually add the menuentry in your grub
config to install.
