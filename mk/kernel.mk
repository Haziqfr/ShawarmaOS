#
# Builds Kernel
#
kernel: $(BUILD_DIR)/kernel.bin


$(BUILD_DIR)/kernel.bin: $(KERNEL_ASM_SRC) | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(KERNEL_ASM_SRC) -o $@