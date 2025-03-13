# build environment
CC := i686-elf-gcc
AS := nasm
LD := i686-elf-gcc
OBJCPY := i686-elf-objcopy
OBJDMP := i686-elf-objdump
ARCH ?= i386

# src tree
SRC_DIR := src
INC_DIR := $(SRC_DIR)/include
ARCH_DIR := $(SRC_DIR)/arch/$(ARCH)
BUILD_DIR := build
KERNEL_DIR := $(SRC_DIR)/kernel
DRIVERS_DIR := $(SRC_DIR)/drivers
LIB_DIR := $(SRC_DIR)/lib
BOOT_DIR := $(ARCH_DIR)/mbr
LOG_DIR := $(BUILD_DIR)/logs

# where find will look for src files (exclude boot from asm arch specific srcs)
C_DIRS := $(KERNEL_DIR) $(ARCH_DIR) $(DRIVERS_DIR) $(LIB_DIR)
AS_DIRS := $(KERNEL_DIR) $(ARCH_DIR) $(LIB_DIR) # LIB_DIR for crt*.asm

# flags
CFLAGS ?= -I $(INC_DIR)/ -ffreestanding -Wall -Wextra -nostdlib -g
LDFLAGS ?= -T $(ARCH_DIR)/linker.ld -ffreestanding -nostdlib -lgcc
ASFLAGS ?= -felf -gdwarf
BSFLAGS ?= -f bin -I $(BOOT_DIR)
OBJCPYFLAGS ?= -O binary
OBJDBGFLAGS ?= --only-keep-debug

# locate all c source files in kernel dir and arch dir
C_SRCS = $(shell find $(C_DIRS) -type f -name '*.c') 
ASM_SRCS = $(shell find $(AS_DIRS) -path $(BOOT_DIR) -prune -o -type f -name '*.asm' -print)
ASM_BOOT = $(BOOT_DIR)/bootsec.asm

# pattern swap to create .o dependencies
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_SRCS))

CRTI_OBJ = $(BUILD_DIR)/lib/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ = $(BUILD_DIR)/lib/crtn.o

OBJS = $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(C_OBJS) $(ASM_OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

$(BUILD_DIR):
	mkdir -p $@

$(LOG_DIR): $(BUILD_DIR)
	mkdir -p $@

$(BUILD_DIR)/kernel/%.o: $(KERNEL_DIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/arch/$(ARCH)/%.o: $(ARCH_DIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/drivers/%.o: $(DRIVERS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel/%.o: $(KERNEL_DIR)/%.asm 
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

# CRT* objs
$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.asm 
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/arch/$(ARCH)/%.o: $(ARCH_DIR)/%.asm
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/kern.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/kern.sym: $(BUILD_DIR)/kern.elf
	$(OBJCPY) $(OBJDBGFLAGS) $< $@

$(BUILD_DIR)/kern.bin : $(BUILD_DIR)/kern.elf
	$(OBJCPY) $(OBJCPYFLAGS) $< $@

$(BUILD_DIR)/bootsec.bin: $(ASM_BOOT) | $(BUILD_DIR)
	$(AS) $(BSFLAGS) $< -o $@
	@echo "ASM OBJECTS: $(ASM_OBJS)"

$(BUILD_DIR)/leos.img: $(BUILD_DIR)/bootsec.bin $(BUILD_DIR)/kern.bin
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BUILD_DIR)/bootsec.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/kern.bin of=$@ bs=512 seek=1 conv=notrunc


.PHONY: clean all qemu debug log
clean:
	rm -rf $(BUILD_DIR)

qemu: $(BUILD_DIR)/leos.img
	qemu-system-$(ARCH) -fda $<

all: $(BUILD_DIR)/leos.img

debug: $(BUILD_DIR)/leos.img $(BUILD_DIR)/kern.sym
	@echo "Run gdb kern.bin ... target remote :1234"
	qemu-system-$(ARCH) -fda $< -s -S
log: $(BUILD_DIR)/leos.img $(LOG_DIR)
	$(OBJDMP) -h $(BUILD_DIR)/kern.elf > $(LOG_DIR)/kern_ld_map.log
	$(OBJDMP) -M intel -D $(BUILD_DIR)/kern.elf > $(LOG_DIR)/kern_disass.log
	$(OBJDMP) --adjust-vma=0x7c00 -M intel -D $(BUILD_DIR)/bootsec.bin -m $(ARCH) -b binary > $(LOG_DIR)/bootsec_disass.log 
	$(OBJDMP) -b binary --adjust-vma=0x100000 -D $(BUILD_DIR)/kern.bin -M intel -m $(ARCH) > $(LOG_DIR)/kern_bin_disass.log
	qemu-system-$(ARCH) -fda $< -d int,cpu_reset -no-reboot -D $(LOG_DIR)/qemu.log
# vm: #ignore last two until I can get GDB working on mac
#	qemu-system-x86_64 -m 4096 -drive file=../../gdb.img -netdev user,id=net0,hostfwd=tcp::10022-:22,hostfwd=tcp::1234-:1234 -device e1000,netdev=net0 &
# mac: $(BUILD_DIR)/leos.img vm
#	qemu-system-$(ARCH) -fda $< -s -S
