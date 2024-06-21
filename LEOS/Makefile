CC := i686-elf-gcc
AS := nasm
LD := i686-elf-ld
ARCH ?= i386

SRC_DIR := src
INC_DIR := $(SRC_DIR)/include
ARCH_DIR := $(SRC_DIR)/arch/$(ARCH)
BUILD_DIR := build
KERNEL_DIR := $(SRC_DIR)/kernel


CFLAGS ?= -I$(INC_DIR) -ffreestanding -Wall -Wextra -O2 -g
LDFLAGS ?= -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
ASFLAGS ?= -felf -g

C_SRCS = $(shell find $(KERNEL_DIR) $(ARCH_DIR) -type f -name '*.c') 
ASM_SRCS = $(shell find $(KERNEL_DIR) -type f -name '*.asm')
ASM_BOOT = $(ARCH_DIR)/mbr/bootsec.asm

C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SRCS))
OBJS = $(C_OBJS) $(ASM_OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(KERNEL_SRCS)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(ARCH_SRCS)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ASM_SRCS)/%.asm | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/kern.bin: $(BUILD_DIR)/%.o | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $< -o $@

$(BUILD_DIR)/bootsec.bin: $(ASM_BOOT) | $(BUILD_DIR)
	$(AS) -f bin $< -o $@

$(BUILD_DIR)/leos.img: $(BUILD_DIR)/bootsec.bin $(BUILD_DIR)/kern.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BUILD_DIR)/bootsec.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/kern.bin =$@ bs=1 count=1 seek=512 conv=notrunc


.PHONY: clean all qemu
clean:
	rm -f $(BUILD_DIR)/**

qemu: $(BUILD_DIR)/leos.img
	qemu-system-$(ARCH) -fda $<

all: $(BUILD_DIR)/leos.img

