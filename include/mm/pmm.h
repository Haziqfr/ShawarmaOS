#ifndef MM_PMM_H
#define MM_PMM_H

// Includes
#include <mm/mm.h>
#include <uapi/genesis/bootparam.h>

// Macro Constants
#define PAGE_SIZE 4096 /* In bytes */
#define USABLE 1

void pmm_init(BootInfo *boot);
phys_addr_t pmm_alloc_frame(void);
void pmm_free_frame(phys_addr_t frame);

#endif /* MM_PMM_H */
