# build environment
CC := i686-elf-gcc
AS := nasm
LD := i686-elf-gcc
ARCH ?= i386

# src tree
SRC_DIR := src
INC_DIR := $(SRC_DIR)/include
ARCH_DIR := $(SRC_DIR)/arch/$(ARCH)
BUILD_DIR := build
KERNEL_DIR := $(SRC_DIR)/kernel
BOOT_DIR := $(ARCH_DIR)/mbr

# where find will look for src files (exclude boot from asm arch specific srcs)
C_DIRS := $(KERNEL_DIR) $(ARCH_DIR)
AS_DIRS := $(KERNEL_DIR) $(ARCH_DIR)

# flags
CFLAGS ?= -I$(INC_DIR)/ -ffreestanding -Wall -Wextra -O2 -g -nostdlib
LDFLAGS ?= -T $(ARCH_DIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
ASFLAGS ?= -felf -g
BSFLAGS ?= -f bin -I $(BOOT_DIR)

# locate all c source files in kernel dir and arch dir
C_SRCS = $(shell find $(C_DIRS) -type f -name '*.c') 
ASM_SRCS = $(shell find $(AS_DIRS) -path $(BOOT_DIR) -prune -o -type f -name '*.asm' -print)
ASM_BOOT = $(BOOT_DIR)/bootsec.asm

# pattern swap to create .o dependencies
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SRCS))
OBJS = $(C_OBJS) $(ASM_OBJS)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/kernel/%.o: $(KERNEL_DIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/arch/$(ARCH)/%.o: $(ARCH_DIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel/%.o: $(KERNEL_DIR)/%.asm 
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/kern.bin: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/bootsec.bin: $(ASM_BOOT) | $(BUILD_DIR)
	$(AS) $(BSFLAGS) $< -o $@
	@echo "ASM OBJECTS: $(ASM_OBJS)"

$(BUILD_DIR)/leos.img: $(BUILD_DIR)/bootsec.bin $(BUILD_DIR)/kern.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BUILD_DIR)/bootsec.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/kern.bin of=$@ bs=1 count=1 seek=512 conv=notrunc


.PHONY: clean all qemu
clean:
	rm -rf $(BUILD_DIR)

qemu: $(BUILD_DIR)/leos.img
	qemu-system-$(ARCH) -fda $<

all: $(BUILD_DIR)/leos.img

