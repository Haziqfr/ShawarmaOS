#ifndef SHAWARMAOS_STDDEF_H
#define SHAWARMAOS_STDDEF_H

// Macro Constants
#define NULL ((void *)0)


// Types
typedef __typeof__(sizeof(0)) size_t;

typedef union {
	long long integer;
	long double floating;
	void* pointer;
} max_align_t;

#define MAX_ALIGN _Alignof(max_align_t)

#endif /* SHAWARMAOS_STDDEF_H */
