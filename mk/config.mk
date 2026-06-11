#
# Tools/Config
#

ASM := /usr/bin/nasm
ASMFLAGS := -f bin

ELFCCFLAGS := -m32 -ffreestanding -fno-builtin -fno-pie -fno-stack-protector -mno-mmx -mno-sse -c
ELFASMFLAGS := -f elf32

CC := /usr/bin/gcc
CC32 := /usr/bin/i686-elf-gcc
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
KERNEL_ASM_SRC := $(wildcard $(SRC)/kernel/*.asm)
KERNEL_C_SRC := $(wildcard $(SRC)/kernel/*.c)
BOOTLOADER_BINS := $(BUILD_DIR)/stage1.bin $(BUILD_DIR)/stage1-5.bin


#
# Macro
#

#
# orchestration
#

.PHONY: clean all kernel run always floppy_image

.DELETE_ON_ERROR:

.DEFAULT_GOAL := all
