OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
	. = 0x9000;

	.text :
	{
	    *(.entry)
		*(.text*)
	}

	.rodata :
	{
		*(.rodata*)
	}

	.data :
	{
		*(.data*)
	}

	.bss :
	{
		*(.bss*)
	}

}
