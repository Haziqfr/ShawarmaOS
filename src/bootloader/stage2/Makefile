ifndef SHAWARMA_OS_BUILD
$(error Please run make from the project root.)
endif


.PHONY: clean

$(BUILD_DIR)/stage2.bin: main.asm 
	$(ASM) $(ASMFLAGS) -o $@ $<



clean:
	rm -rf $(BUILD_DIR)/stage2.bin
