BUILD="../tmp_build"

nasm -f bin -o $BUILD/boot.bin bootsec.asm

dd if=/dev/zero of=$BUILD/floppy.img bs=512 count=2880
dd if=$BUILD/boot.bin of=$BUILD/floppy.img bs=512 count=1 conv=notrunc
echo "BOO" > $BUILD/deadbeef.bin
dd if=$BUILD/deadbeef.bin of=$BUILD/floppy.img bs=1 count=4 seek=512 conv=notrunc
rm $BUILD/*.bin
qemu-system-i386 -fda $BUILD/floppy.img
