export SHAWARMA_OS_BUILD := 1


#
# Tools/Config
#

ASM := nasm
CC := gcc
LD := ld
ASMFLAGS := -f bin


#
# Build folders
#

BUILD_DIR := build
SRC := src
BOOTLOADER_DIR := src/bootloader
BOOTLOADER_BINS := $(BUILD_DIR)/stage1.bin $(BUILD_DIR)/stage2.bin


#
# Macro
#



#
# orchestration
#

.PHONY: clean all kernel run always floppy_image 

.DELETE_ON_ERROR:

.DEFAULT_GOAL := all



#
# All
#

all: floppy_image




#
# Floppy image dependency
#

floppy_image: $(BUILD_DIR)/main_floppy.img


#
# Creates floppy image
#

$(BUILD_DIR)/main_floppy.img: $(BOOTLOADER_BINS) | $(BUILD_DIR)
	dd if=/dev/zero of=$@ bs=512 count=2880 status=progress
	dd if=$(BUILD_DIR)/stage1.bin of=$@ conv=notrunc
	dd if=$(BUILD_DIR)/stage2.bin of=$@ seek=1 conv=notrunc bs=512


#	cp $(BUILD_DIR)/stage1.bin $(BUILD_DIR)/main_floppy.img
#	truncate -s 1440k $(BUILD_DIR)/main_floppy.img





#
# BOOTLOADER
#

#
# Creates stage-1 bootloader
#


$(BUILD_DIR)/stage1.bin: | $(BUILD_DIR) 
	$(MAKE) -C $(BOOTLOADER_DIR)/stage1 ASM="$(ASM)" BUILD_DIR="$(abspath $(BUILD_DIR))" ASMFLAGS="$(ASMFLAGS)"


#
# Creates stage-2 bootloader
#


$(BUILD_DIR)/stage2.bin: | $(BUILD_DIR)
	$(MAKE) -C $(BOOTLOADER_DIR)/stage2 ASM="$(ASM)" BUILD_DIR="$(abspath $(BUILD_DIR))" ASMFLAGS="$(ASMFLAGS)"



#
# Builds Kernel
#
kernel: $(BUILD_DIR)/kernel.bin


$(BUILD_DIR)/kernel.bin:








#
# Run
#
run: $(BUILD_DIR)/main_floppy.img
	qemu-system-i386 -fda $(BUILD_DIR)/main_floppy.img



#
# always runs
# 	- Creates BUILD_DIR if not created
#

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)





#
# Removes everything from BUILD_DIR 
#

clean: 
	$(MAKE) -C $(BOOTLOADER_DIR)/stage1 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	$(MAKE) -C $(BOOTLOADER_DIR)/stage2 BUILD_DIR=$(abspath $(BUILD_DIR)) clean
	rm -rf $(BUILD_DIR)
