// Author: strawberryhacker

#include "registers.h"
#include "utilities.h"
#include "clock.h"
#include "gpio.h"
#include "usb.h"
#include "print.h"
#include "stdint.h"
#include "stddef.h"

//--------------------------------------------------------------------------------------------------

// Just a little information about the physical configuration on the board.

// TX     : PA8
// RX     : PA9
// LED    : PA14 and PA15
// BUTTON : PA22 and PA23

//--------------------------------------------------------------------------------------------------

static void wait() {
	for (u32 i = 0; i < 5000000; i++) {
		__asm__("nop");
	}
}

//--------------------------------------------------------------------------------------------------

void main() {
	clock_init();
	print_init();
	usb_init();

	PORTA->DIRSET = 1 << 14 | 1 << 15;
	
	while (1) {
		print("Lemon is yellow, oui?\n");
		wait();
	}
}
