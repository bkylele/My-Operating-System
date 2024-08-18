#include <terminal.h>
#include <stdio.h>
#include <stdarg.h>


int printf(const char* restrict format, ...) {
    va_list args;
    va_start(args, format);

    // for now naive implementation, flush after every char
    while (*format) {
        if (*format == '%') {
            ++format;

            switch (*format) {
                case 'd':
                    terminal_writedec(va_arg(args, size_t));
                    break;
                case 's':
                    terminal_writestring(va_arg(args, const char*));
                    break;
                case 'x':
                    terminal_writehex(va_arg(args, size_t));
                    break;
            }

            ++format;
        } else {
            terminal_putchar(*format);
            ++format;
        }
    }

    va_end(args);
    return 0;
}

int putchar(int c) {
    return 0;
}

int puts(const char* s) {
    return 0;
}

