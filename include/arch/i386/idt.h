#pragma once
#include <arch/i386/stdint.h>

struct idt_entry {
    uint16_t offset_low;
    uint16_t seg_selec;
    uint8_t reserved_zero;
    uint8_t type_attribute;

};


