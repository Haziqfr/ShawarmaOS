#
# Creates stage-1 bootloader
#


$(BUILD_DIR)/stage1.bin: $(STAGE1_ASM_SRC) | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(STAGE1_ASM_SRC) -o $@


#
# Creates stage-2 bootloader
#


$(BUILD_DIR)/stage2.bin: $(STAGE2_ASM_SRC) | $(BUILD_DIR)
	$(ASM) $(ASMFLAGS) $(STAGE2_ASM_SRC) -o $@
