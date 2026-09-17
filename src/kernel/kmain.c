#include <stdio.h>
#include <uapi/genesis/bootparam.h>
#include <drivers/timer/timer.h>
#include <drivers/serial/serial.h>
#include <arch/i386/interrupt/pic.h>
#include <arch/i386/interrupt/idt.h>
#include <drivers/video/vga.h>
#include <mm/pmm.h>
#include <mm/vmm.h>

/*
 * Magic = crc32("ShawarmaOS Boot Protocol")
 */
#define MAGIC 0x88FF1A3B

extern void reload_gdt(void);

void kernel_main(phys_addr_t boot_phys)
{
	BootInfo* boot = (BootInfo*)PHYS2VIRT(boot_phys);
	vga_clear();
	vga_write("Hello again from ShawarmaOS\n");

	idt_init();
	kprintf("[INFO] IDT Initialized\n");

	pic_init();
	kprintf("[INFO] PIC Initialized\n");

	serial_init();
	kprintf("[INFO] Serial Initialized\n");

	pmm_init(boot);
	kprintf("[INFO] PMM Initialized\n");

	vmm_init();
	kprintf("[INFO] VMM Initialized\n");

	reload_gdt();
	kprintf("[INFO] GDT Reloaded\n");

	timer_init(100);
	kprintf("[INFO] Timer Initialized\n");

	__asm__ volatile("sti");
	kprintf("[INFO] Interrupts enabled\n");


	if (boot->magic != MAGIC) {
		kprintf("Invalid boot info. Go cry now\n");
		return;
	}

	kprintf("Boot Info is correct. Celebrate!!!\n");

	for (;;) {
		__asm__ volatile("hlt");
	}
}
