#include <stdint.h>
#include "tty/tty.h"
#include "io/io.h"

void _cstart() {
	tty_print("Hello, Kernel World!\n");
	uint8_t test = _test_ams();
	if (test == 1) {
		tty_print("Houston, we got a problem\n");
	} 
	if (test == 4) {
		tty_print("The asm stuff worked!?\n");
	}
}
