#pragma once
#include <arch/i386/stdint.h>

struct idt_entry {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t reserved_zero;
	uint8_t type_attribute;
	uint16_t offset_high;
} __attribute__((packed));

struct idtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[256];
extern void idt_load(uint32_t ptr);

void idt_init(void);
