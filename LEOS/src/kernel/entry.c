#include <stdint.h>
#include "tty/tty.h"

void _cstart() {
	tty_clear();	
	tty_test();
	tty_print("This should be \n on two lines");
	tty_print("A little more ?\n? scrolling?");
}
