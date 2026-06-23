#include <arch/i386/idt.h>
#include <drivers/video/vga.h>

void kernel_main(void)
{
	volatile char *vga = (volatile char *)0xB8000;
	vga[0] = 'H';
	vga[1] = 0x0C;
	vga[2] = 'i';
	vga[3] = 0x0C;

	vga_clear();
	vga_write("Hello again from ShawarmaOS\n");

	idt_init();
}
