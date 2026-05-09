ifndef SHAWARMA_OS_BUILD
$(error Please run make from the project root.)
endif


.PHONY: clean



$(BUILD_DIR)/stage1.bin: boot.asm 
	$(ASM) -o $@ $(ASMFLAGS) $<


clean:
	rm -rf $(BUILD_DIR)/stage1.bin
