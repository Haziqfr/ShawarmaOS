#
# Builds Kernel
#
kernel: $(BUILD_DIR)/kernel.bin


$(BUILD_DIR)/kernel.bin: $(KERNEL_OBJS) | always
	$(LD) -nostdlib -T src/kernel/linker.ld -o $(BUILD_DIR)/kernel.elf $(KERNEL_OBJS)
	objcopy -O binary $(BUILD_DIR)/kernel.elf $@


$(BUILD_DIR)/kernel/%.o: $(SRC)/kernel/%.c | always
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/kernel/%.o: $(SRC)/kernel/%.asm | always
	$(AS) $(ASFLAGS_ELF) $< -o $@