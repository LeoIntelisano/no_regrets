#include <stdint.h>
#include "tty/tty.h"

void _cstart() {
	tty_clear();	
	tty_test();
}
