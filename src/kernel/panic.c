#include <panic.h>
#include <stdio.h>

__attribute__((noreturn))
void panic(const char *reason)
{
	__asm__ volatile("cli");

	kprintf("\n");
	kprintf("========================================\n");
	kprintf("          OOPS! KERNEL PANIC\n");
	kprintf("========================================\n\n");

	kprintf("welp. this is awkward.\n");
	kprintf("The kernel has encountered a fatal error.\n\n");

	kprintf("REASON: %s\n", reason ? reason : "(unknown)");
	kprintf("\nSYSTEM HALTED. REBOOT REQUIRED.\n");

	for (;;) {
		__asm__ volatile("hlt");
	}
}
