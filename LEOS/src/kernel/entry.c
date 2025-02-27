#include <stdint.h>
#include "tty/tty.h"
#include "io/io.h"
#include "drivers/dt.h"
#include "drivers/vga.h"


void _cstart() {
	tty_clear();
	tty_print("Hello, Kernel World!\n");
	uint8_t test = _test_asm();
	if (test == 1) {
		tty_print("Houston, we got a problem\n");
	} 
	if (test == 4) {
		tty_print("The asm stuff worked!?\n");
	}
	link_test();
	tty_test();
	tty_set_attr(0x3);
	tty_print("Is the color different");
}
 