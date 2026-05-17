#
# Tools/Config
#

ASM := /usr/bin/nasm
ASMFLAGS := -f bin

CC := /usr/bin/gcc
LD := /usr/bin/ld

DD := /usr/bin/dd


#
# Build folders
#

BUILD_DIR := build
SRC := src
BOOTLOADER_DIR := src/bootloader
STAGE1_ASM_SRC := $(wildcard $(BOOTLOADER_DIR)/stage1/*.asm)
STAGE1-5_ASM_SRC := $(wildcard $(BOOTLOADER_DIR)/stage1.5/*.asm)
STAGE2_ASM_SRC := $(wildcard $(BOOTLOADER_DIR)/stage2/*.asm)
BOOTLOADER_BINS := $(BUILD_DIR)/stage1.bin $(BUILD_DIR)/stage2.bin $(BUILD_DIR)/stage1-5.bin


#
# Macro
#

#
# orchestration
#

.PHONY: clean all kernel run always floppy_image

.DELETE_ON_ERROR:

.DEFAULT_GOAL := all
