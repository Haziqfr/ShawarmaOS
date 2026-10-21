#ifndef MM_MM_H
#define MM_MM_H

#include <arch/i386/stdint.h>

// Types
typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;
#define PHYS_ADDR_MAX UINT32_MAX

#define KERNEL_VIRT_ADDR 0xC0000000

#define MMIO_BASE_START 0xE0000000
#define MMIO_BASE_END   0xF8000000



typedef struct {
	uint32_t entries[1024];
} __attribute__((aligned(4096))) page_directory_t;

typedef struct {
	uint32_t entries[1024];
} __attribute__((aligned(4096))) page_table_t;

#endif // MM_MM_H
