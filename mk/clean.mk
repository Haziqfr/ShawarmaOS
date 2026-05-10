#
# CLEAN
#

clean:
	$(MAKE) -C $(BOOTLOADER_DIR)/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C $(BOOTLOADER_DIR)/stage2 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)
