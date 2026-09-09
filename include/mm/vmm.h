#ifndef MM_VMM_H
#define MM_VMM_H

#define PRESENT 1
#define RW (1 << 1)
#define US (1 << 2)
#define GLOBAL (1 << 8)

void vmm_identity_map_kernel(void);
void vmm_higher_half_map_kernel(void);

#endif // MM_VMM_H
