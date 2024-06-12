/* kernel.c */
void _start() {
	char* vga = (char*) 0xb8000;
	*vga = 'X';
}
