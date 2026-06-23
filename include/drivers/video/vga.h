#pragma once

#include <arch/i386/stdint.h>

void vga_clear(void);
void vga_putc(char c);
void vga_write(const char *str);