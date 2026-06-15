#include <arch/i386/idt.h>

extern void isr0();
extern void isr1();


struct idt_entry idt[256];
struct idtr idt_ptr;


static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
        idt[num].offset_low = (base & 0xFFFF);
        idt[num].offset_high = ((base >> 16) & 0xFFFF);

        idt[num].reserved_zero = 0;
        idt[num].selector = sel;
        idt[num].type_attribute = flags;
}




void idt_init(void)
{
        idt_ptr.limit = (sizeof(struct idt_entry) * 256) - 1;
        idt_ptr.base = (uint32_t)&idt;

        idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
        idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);


        idt_load((uint32_t)&idt_ptr);
}


