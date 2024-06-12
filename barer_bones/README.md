### This is the src from following along with NICK BLUNDELL'S OS TUTORIAL
## 16-bit Real Mode
Shows asm source for BIOS calls to read sectors from a floppy\
Print using int 10h\
Setup GDT and Segement Entries\
Swap into protected mode

## 32-bit Protected Mode
Sets up printing using vga at 0xb8000\
boostraps c and calls kernel.c methods\
more aptly, calls whatever resides at 0x1000 in memory\
Lets hope 000000 corresponds to `_start()`!

## C attributes
Also investigates the compilation and linking process.\
\ 
\ 
\
Helpful shell scripts found in src
