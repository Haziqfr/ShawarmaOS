#
# Run
#
run: $(BUILD_DIR)/main_floppy.img
	@qemu-system-i386 -d int,cpu_reset -D qemu.log -no-reboot \
	-no-shutdown -fda build/main_floppy.img

#
# Debug
#
debug: OPT_FLAGS := -g -Og -fno-omit-frame-pointer -fno-optimize-sibling-calls
debug: clean $(BUILD_DIR)/main_floppy.img
	@qemu-system-i386 -d int,cpu_reset -D qemu.log -no-reboot \
 	-no-shutdown -fda build/main_floppy.img -s -S
