BUILD='../build'
OBJ='boot'
TARGET='i386'

nasm -f bin -o $BUILD/$OBJ.bin $OBJ.asm
qemu-system-$TARGET -drive format=raw,file=$BUILD/$OBJ.bin
