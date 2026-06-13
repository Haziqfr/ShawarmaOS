#
# Creates stage-1 bootloader
#


$(BUILD_DIR)/stage1.bin: $(STAGE1_ASM_SRC) | always
	$(AS) $(ASFLAGS) $(STAGE1_ASM_SRC) -o $@



#
# Creates stage-1.5 bootloader
#


$(BUILD_DIR)/stage1-5.bin: $(STAGE1_5_ASM_SRC) | always
	$(AS) $(ASFLAGS) $(STAGE1_5_ASM_SRC) -o $@

