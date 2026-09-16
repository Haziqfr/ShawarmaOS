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

void kernel_main_high(BootInfo *boot);
extern void enable_paging(void);
extern void reload_gdt(void);

void kernel_main(BootInfo *boot)
{
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

	//vmm_identity_map_kernel();
	kprintf("[INFO] Identity mapped the kernel\n");

	//vmm_higher_half_map_kernel();
	kprintf("[INFO] Higher half mapped the kernel\n");

	//enable_paging();
	kprintf("[INFO] Paging Enabled\n");
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
