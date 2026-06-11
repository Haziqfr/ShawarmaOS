void kernel_main(void)
{
	volatile char* vga = (volatile char*)0xB8000;
	vga[0] = 'H';
	vga[1] = 0xEC;
}
