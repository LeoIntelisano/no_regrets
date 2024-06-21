#!/bin/zsh
BUILD="../tmp_build"

DEBUG_MODE=false
while getopts ":hd" opt; do
	case ${opt} in
		d )
			DEBUG_MODE=true
			echo "debug"
			;;
		:)
			;;
	esac
done



nasm -f bin -g -o $BUILD/boot.bin bootsec.asm

dd if=/dev/zero of=$BUILD/floppy.img bs=512 count=2880
dd if=$BUILD/boot.bin of=$BUILD/floppy.img bs=512 count=1 conv=notrunc
echo "BOO" > $BUILD/deadbeef.bin
dd if=$BUILD/deadbeef.bin of=$BUILD/floppy.img bs=1 count=4 seek=512 conv=notrunc
rm $BUILD/*.bin
if [ "$DEBUG_MODE" = true ]; then
	qemu-system-i386 -fda $BUILD/floppy.img -gdb tcp::1234 -S
else
	qemu-system-i386 -fda $BUILD/floppy.img
fi
