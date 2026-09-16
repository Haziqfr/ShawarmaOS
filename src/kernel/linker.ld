OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0xC0009000;

    _kernel_phys_start = 0x9000;
	_kernel_virt_start = .;

	.text ALIGN(4K) : AT(ADDR(.text) - _kernel_virt_start + _kernel_phys_start)
	{
	    *(.entry)
		*(.text*)
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - _kernel_virt_start + _kernel_phys_start)
	{
		*(.rodata*)
	}

	.data : AT(ADDR(.data) - _kernel_virt_start + _kernel_phys_start)
	{
		*(.data*)
	}

	.bss : AT(ADDR(.bss) - _kernel_virt_start + _kernel_phys_start)
	{
	    *(COMMON)
		*(.bss*)
	}

	_kernel_virt_end = .;
	_kernel_phys_end = LOADADDR(.bss) + SIZEOF(.bss);

}
