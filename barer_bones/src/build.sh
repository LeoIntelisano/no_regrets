BUILD='../build'
AOBJ='boot'
AENTRY='entry'
COBJ='kernel'
TARGET='i386'
CC='i686-elf-gcc'
LD='i686-elf-ld'
MEMORY=0x1000
NAME='os-image'

nasm -f bin -o $BUILD/$AOBJ.bin $AOBJ.asm
nasm -f elf -o $BUILD/$AENTRY.o $AENTRY.asm
$CC -ffreestanding -c $COBJ.c -o $BUILD/$COBJ.o
$LD -o $BUILD/$COBJ.bin -Ttext $MEMORY $BUILD/$AENTRY.o $BUILD/$COBJ.o --oformat binary 
cat $BUILD/$AOBJ.bin $BUILD/$COBJ.bin > $BUILD/$NAME 
qemu-system-$TARGET -fda $BUILD/$NAME -boot a
