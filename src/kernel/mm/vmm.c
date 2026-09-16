#include <mm/vmm.h>
#include <mm/pmm.h>
#include <arch/i386/stdint.h>
#include <stddef.h>
#include <string.h>

static page_directory_t* kernel_pd;
static phys_addr_t kernel_pd_phys_addr;

void vmm_init(void)
{
	kernel_pd_phys_addr = (uintptr_t)pmm_alloc_page();
	kernel_pd = (page_directory_t*)PHYS2VIRT(kernel_pd_phys_addr);
	memset(kernel_pd, 0, sizeof(page_directory_t));

	for (size_t i = 0; i < 0x400000; i += 0x1000) {
		vmm_map_page(KERNEL_VIRT_ADDR + i, i, VMM_FLAG_WRITABLE);
	}

	load_page_dir(kernel_pd_phys_addr);
}

void vmm_map_page(virt_addr_t virt, phys_addr_t phys, vmm_flags_t flags)
{
	uint32_t pd_idx = pde_index(virt);
	uint32_t pt_idx = pte_index(virt);

	page_table_t* pt = vmm_get_or_create_pt(pd_idx);

	if (!pt) return;

	pt->entries[pt_idx] = (phys & 0xFFFFF000) | flags | VMM_FLAG_PRESENT;

	tlb_flush_single(virt);
}

void vmm_unmap_page(virt_addr_t virt)
{
	uint32_t pd_idx = pde_index(virt);
	uint32_t pt_idx = pte_index(virt);
	uint32_t pde = kernel_pd->entries[pd_idx];

	if (!(pde & VMM_FLAG_PRESENT)) return;

	page_table_t* pt = (page_table_t*)PHYS2VIRT(pde & 0xFFFFF000);

	pt->entries[pt_idx] = 0;

	tlb_flush_single(virt);

}

page_table_t* vmm_get_or_create_pt(uint32_t pd_index)
{
	uint32_t pde = kernel_pd->entries[pd_index];

	if (pde & VMM_FLAG_PRESENT) {
		uintptr_t pt_phys = pde & 0xFFFFF000;
		return (page_table_t*)PHYS2VIRT(pt_phys);
	}

	uintptr_t new_pt_phys = (uintptr_t)pmm_alloc_page();
	if (!new_pt_phys) return NULL; // OOM

	page_table_t* pt_virt = (page_table_t*)PHYS2VIRT(new_pt_phys);
	memset(pt_virt, 0, sizeof(page_table_t));

	kernel_pd->entries[pd_index] = new_pt_phys | VMM_FLAG_PRESENT | VMM_FLAG_WRITABLE;

	return pt_virt;
}
