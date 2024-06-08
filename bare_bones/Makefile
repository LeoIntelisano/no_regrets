CC = i686-elf-gcc
AS = nasm

TARGET = MYOS

SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./inc
ISO_DIR = ./isodir

#Default CFLAGS:
CFLAGS ?= -O2 -g -std=gnu99

# Mandatory flags
CFLAGS :=$(CFLAGS) -Wall -Wextra -ffreestanding -I$(INC_DIR)
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc 
ASFLAGS = -felf32

C_SRCS = $(wildcard $(SRC_DIR)/*.c)
ASM_SRCS = $(wildcard $(SRC_DIR)/*.asm)
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SRCS))
OBJS = $(C_OBJS) $(ASM_OBJS)

# Output file
OUTPUT = $(BUILD_DIR)/$(TARGET).bin
ISO = $(BUILD_DIR)/$(TARGET).iso


# Default target
all: $(OUTPUT) $(ISO)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build C source files
compile_c: $(BUILD_DIR) $(C_OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

assemble_asm: $(BUILD_DIR) $(ASM_OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(OUTPUT): compile_c assemble_asm
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(ISO_DIR):
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(OUTPUT) $(ISO_DIR)/boot/$(TARGET).bin
	echo 'menuentry "$(TARGET)" {\n	multiboot /boot/$(TARGET).bin\n}' > $(ISO_DIR)/boot/grub/grub.cfg

$(ISO): $(OUTPUT) $(ISO_DIR)
	grub-mkrescue -o $@ $(ISO_DIR)
qemu: $(ISO)
	qemu-system-i386 -cdrom $(ISO)
clean:
	rm -rf $(BUILD_DIR)/*.o $(OUTPUT) $(ISO) $(ISO_DIR)

.PHONY: all clean compile_c assemble_asm
