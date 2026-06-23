#include <arch/i386/isr.h>
#include <drivers/video/vga.h>

void isr_handler(struct regs *r)
{
	vga_write("EXCEPTION\n");
	for (;;)
		__asm__("hlt");
}
