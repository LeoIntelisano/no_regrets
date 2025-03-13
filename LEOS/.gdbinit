set disassembly-flavor intel
symbol-file build/kern.elf
target remote :1234
b *0x100000
b _cstart