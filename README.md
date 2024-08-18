# MinimalOS
An exploratory project implementing an operating system for Intel's 32-bit Protected Mode.

> NOTE: This is a Toy OS, not intended for daily driving (and probably not for a while).

## Build

### Dependencies
This project requires a GCC Cross-Compiler set up for i686-elf. **This will not
work with an x86_64-elf cross compiler**. See how to build gcc on [OsDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler).
Assuming you have GCC, GAS, and Make, you will also need:

- Grub
- xorriso
- QEMU (Optionally for testing in VM)

### To Build

``` bash
$ make myos.iso
```
To create the cdrom image or:

``` bash
$ make qemu
```
To run in a VM.


## Roadmap

- [X] Terminal Interface
- [X] Global Descriptor Table
- [X] Interrupt Descriptor Table
- [ ] System Calls
- [ ] Paging
- [ ] Tasking

