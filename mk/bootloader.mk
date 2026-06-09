#
# Creates stage-1 bootloader
#


$(BUILD_DIR)/stage1.bin: $(STAGE1_ASM_SRC) | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(STAGE1_ASM_SRC) -o $@



#
# Creates stage-1.5 bootloader
#


$(BUILD_DIR)/stage1-5.bin: $(STAGE1-5_ASM_SRC) | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(STAGE1-5_ASM_SRC) -o $@

