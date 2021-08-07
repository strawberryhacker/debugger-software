// Author: strawberryhacker

#include "registers.h"
#include "utilities.h"
#include "stdint.h"
#include "stddef.h"

//--------------------------------------------------------------------------------------------------

// Just a little information about the physical configuration on the board.

// TX     : PA8
// RX     : PA9
// LED    : PA14 and PA15
// BUTTON : PA22 and PA23

//--------------------------------------------------------------------------------------------------

typedef enum {
	PIN_FUNCTION_A,
	PIN_FUNCTION_B,
	PIN_FUNCTION_C,
	PIN_FUNCTION_D,
	PIN_FUNCTION_E,
	PIN_FUNCTION_F,
	PIN_FUNCTION_G,
	PIN_FUNCTION_H,
	PIN_FUNCTION_I
} PinFunction;

//--------------------------------------------------------------------------------------------------

static void clock_init() {
	// Disable the prescaler such that the output frequency is 8 MHz.
	SYSCTRL->OSC8M &= ~(0b11 << 8);
}

//--------------------------------------------------------------------------------------------------

static void set_pin_function(Port* port, u32 pin, PinFunction function) {
	port->PMUX[pin / 2] = (port->PMUX[pin / 2] & ~(0xf << (4 * (pin & 1)))) | (function << (4 * (pin & 1)));
	port->PINCFG[pin] = 1;
}

//--------------------------------------------------------------------------------------------------

static void print_char(char c) {
	while ((UART0->INTFLAG & 1) == 0);
	UART0->DATA = c;
}

//--------------------------------------------------------------------------------------------------

void print(const char* data, ...) {
	static char print_buffer[512];
	va_list arguments;
	va_start(arguments, data);
	u32 size = format_string(data, print_buffer, 512, arguments);

	for (u32 i = 0; i < size; i++) {
		print_char(print_buffer[i]);
	}
}

//--------------------------------------------------------------------------------------------------

static void wait() {
	for (u32 i = 0; i < 100000; i++) {
		__asm__("nop");
	}
}

//--------------------------------------------------------------------------------------------------

void main() {
	clock_init();

	PORTA->DIRSET = 1 << 8;
	PORTA->DIRCLR = 1 << 9;
	set_pin_function(PORTA, 8, PIN_FUNCTION_C);
	set_pin_function(PORTA, 9, PIN_FUNCTION_C);

	PM->APBCMASK |= 0xff;
	
	GCLK->CLKCTRL = 1 << 14 | 0x14;
	
	UART0->CTRLA = 1 << 30 | 1 << 20 | 1 << 2;
	UART0->CTRLB = 1 << 16 | 1 << 17;
	while (UART0->SYNCBUSY & (1 << 2));
	UART0->BAUD = 63019;
	UART0->CTRLA |= 1 << 1;
	while (UART0->SYNCBUSY & (1 << 1));

	PORTA->DIRSET = 1 << 14 | 1 << 15;

	print("This is a test {u}\n", 234);
	
	while (1) {
		PORTA->OUTSET = 1 << 14 | 1 << 15;
		wait();
		PORTA->OUTCLR = 1 << 14 | 1 << 15;
		wait();
	}
}
