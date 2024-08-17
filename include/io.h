#ifndef __MYOS__IO_H
#define __MYOS__IO_H

#include <stdint.h>


inline uint8_t inb(volatile uint16_t port) {
    volatile uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

inline void outb(volatile uint16_t port, volatile uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}


#endif /* ifndef __MYOS__IO_H */
