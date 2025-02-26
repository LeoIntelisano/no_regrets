#include <stdint.h>
#include "tty/tty.h"
#include "io/io.h"

void _cstart() {
<<<<<<< HEAD
	tty_print("Hello, Kernel World!\n");
	uint8_t test = _test_ams();
	if (test == 1) {
		tty_print("Houston, we got a problem\n");
	} 
	if (test == 4) {
		tty_print("The asm stuff worked!?\n");
	}
=======
	tty_clear();	
	tty_print("Welcome to LEOS");
>>>>>>> 8d6131bb19d0c2f12c8412e8a780f7565c0e381f
}
