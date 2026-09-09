#include <mm/vmm.h>
#include <mm/pmm.h>
#include <stdio.h>

#define VIRT_HIGHER_HALF_ADDR 0xC0000000

extern void load_page_dir(uintptr_t);

/*
 Global Kernel Page Directory
*/
static uint32_t* kernel_pd = 0;

void vmm_identity_map_kernel(void)
{
	if (!kernel_pd) {
		kernel_pd = pmm_alloc_page();

		// Clear PD to avoid garbage values acting as present pages
		for (uint16_t i = 0; i < 1024; i++) kernel_pd[i] = 0;
	}

	uint32_t *iden_pt = pmm_alloc_page();

	kernel_pd[0] = ((uintptr_t)iden_pt & 0xFFFFF000) | PRESENT | RW;

	for (uint16_t i = 0; i < 1024; i++) {
		iden_pt[i] = ((i * 0x1000) & 0xFFFFF000) | PRESENT | RW;
	}

	load_page_dir((uintptr_t)kernel_pd);
	kprintf("[INFO] Loaded page table\n");
}

void vmm_higher_half_map_kernel(void)
{
	if (!kernel_pd) {
		kernel_pd = pmm_alloc_page();

		// Clear PD to avoid garbage values acting as present pages
		for (uint16_t i = 0; i < 1024; i++) kernel_pd[i] = 0;
	}

	uint32_t *higher_pt = pmm_alloc_page();
	uint32_t pde = VIRT_HIGHER_HALF_ADDR >> 22;

	kernel_pd[pde] = ((uintptr_t)higher_pt & 0xFFFFF000) | PRESENT | RW;

	for (uint32_t i = 0; i < 1024; i++) {
		higher_pt[i] = (((i * 0x1000) & 0xFFFFF000) + 0x9000) | PRESENT | RW;
	}

	load_page_dir((uintptr_t)kernel_pd);
	kprintf("[INFO] Loaded page table\n");
}
