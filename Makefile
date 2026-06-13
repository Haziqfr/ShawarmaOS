#Order: config -> bootloader -> kernel -> image -> run -> clean

# config
include mk/config.mk

# all
all: floppy_image

# image creation rules
include mk/image.mk

# bootloader rules
include mk/bootloader.mk

# kernel rules
include mk/kernel.mk

# run rules
include mk/qemu.mk

# always runs
# 	- Creates BUILD_DIR if not created
always:
	@mkdir -p $(BUILD_DIR)/kernel
	@mkdir -p $(BUILD_DIR)/stage1.5

# clean
#  |-Removes everything from BUILD_DIR
include	mk/clean.mk
