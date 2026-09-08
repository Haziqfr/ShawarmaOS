#include <mm/vmm.h>
#include <mm/pmm.h>
#include <stdio.h>

extern void load_page_dir(uintptr_t);

void vmm_identity_map_kernel(void)
{
	uint32_t *iden_pd = pmm_alloc_page();
	uint32_t *iden_pt = pmm_alloc_page();

	iden_pd[0] = ((uintptr_t)iden_pt & 0xFFFFF000) | PRESENT | RW;

	for (int i = 0; i < 1024; i++) {
		iden_pt[i] = ((i * 0x1000) & 0xFFFFF000) | PRESENT | RW;
	}

	load_page_dir((uintptr_t)iden_pd);
	kprintf("[INFO] Loaded page table\n");
}
