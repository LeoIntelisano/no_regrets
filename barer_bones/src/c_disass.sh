i686-elf-gcc -ffreestanding -c basic.c -o ../build/basic.o
i686-elf-objdump -d ../build/basic.o
i686-elf-ld -o ../build/basic.bin -Ttext 00 --oformat binary ../build/basic.o
ndisasm -b 32 ../build/basic.bin > ../build/basic.dis
cat ../build/basic.dis
