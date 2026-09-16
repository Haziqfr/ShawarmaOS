#ifndef MM_VMM_H
#define MM_VMM_H

#include <arch/i386/stdint.h>

// Flags
typedef enum {
	VMM_FLAG_PRESENT       = (1 << 0),
	VMM_FLAG_WRITABLE      = (1 << 1),
	VMM_FLAG_USER          = (1 << 2),
	VMM_FLAG_WRITETHROUGH  = (1 << 3),
	VMM_FLAG_CACHE_DISABLE = (1 << 4),
	VMM_FLAG_GLOBAL        = (1 << 8),
} vmm_flags_t;

#define KERNEL_VIRT_ADDR 0xC0000000

#define MMIO_BASE_START 0xE0000000
#define MMIO_BASE_END   0xF8000000

// Types
typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;
#define PHYS_ADDR_MAX UINT32_MAX

typedef struct {
	uint32_t entries[1024];
} __attribute__((aligned(4096))) page_directory_t;

typedef struct {
	uint32_t entries[1024];
} __attribute__((aligned(4096))) page_table_t;

void vmm_init(void);
void vmm_map_page(virt_addr_t virt, phys_addr_t phys, vmm_flags_t flags);
void vmm_unmap_page(virt_addr_t virt);
uintptr_t vmm_get_phys(virt_addr_t virt);
page_table_t* vmm_get_or_create_pt(uint32_t pd_index);

extern void load_page_dir(uintptr_t phys_addr);
static inline void tlb_flush_single(uintptr_t virt_addr)
{
	__asm__ volatile("invlpg (%0)" : : "r"(virt_addr) : "memory");
}
static inline uintptr_t phys_to_virt(uintptr_t phys)
{
	return phys + KERNEL_VIRT_ADDR;
}

static inline uintptr_t virt_to_phys(uintptr_t virt)
{
	return virt - KERNEL_VIRT_ADDR;
}

#define PHYS2VIRT(phys) phys_to_virt(phys)
#define VIRT2PHYS(virt) virt_to_phys(virt)

static inline uint32_t pde_index(uintptr_t virt)
{
	return (virt >> 22) & 0x3FF;
}

static inline uint32_t pte_index(uintptr_t virt)
{
	return (virt >> 12) & 0x3FF;
}

static inline uint32_t page_offset(uintptr_t virt)
{
	return virt & 0xFFF;
}

#endif // MM_VMM_H
