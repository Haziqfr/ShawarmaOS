#
# Builds Kernel
#
kernel: $(BUILD_DIR)/kernel.bin


$(BUILD_DIR)/kernel.bin: $(KERNEL_ASM_SRC) $(KERNEL_C_SRC) | $(BUILD_DIR)
	$(ASM) $(ELFASMFLAGS) $(KERNEL_ASM_SRC) -o $(BUILD_DIR)/kernel_asm.o
	$(CC32) $(ELFCCFLAGS) $(KERNEL_C_SRC) -o $(BUILD_DIR)/kernel.o
	i686-elf-ld -m elf_i386 -T src/kernel/linker.ld -o build/kernel.elf build/kernel_asm.o build/kernel.o
	objcopy -O binary build/kernel.elf build/kernel.bin

