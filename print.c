// Author: strawberryhacker

#include "print.h"
#include "clock.h"
#include "gpio.h"

//--------------------------------------------------------------------------------------------------

void print_init() {
    gpio_output(PORTA, 8);
	gpio_set_function(PORTA, 8, GPIO_FUNCTION_C);

	gpio_input(PORTA, 9);
	gpio_set_function(PORTA, 9, GPIO_FUNCTION_C);

	configure_peripheral_clock(0x14, 0);
	
	UART0->CTRLA = 1 << 30 | 1 << 20 | 1 << 2;
	UART0->CTRLB = 1 << 16 | 1 << 17;
	while (UART0->SYNCBUSY & (1 << 2));
	UART0->BAUD = 65117;
	UART0->CTRLA |= 1 << 1;
	while (UART0->SYNCBUSY & (1 << 1));
}

//--------------------------------------------------------------------------------------------------

static void print_char(char c) {
	while ((UART0->INTFLAG & 1) == 0);
	UART0->DATA = c;
}

//--------------------------------------------------------------------------------------------------

void print(const char* text, ...) {
    static char print_buffer[512];
	va_list arguments;
	va_start(arguments, text);
	u32 size = format_string(text, print_buffer, 512, arguments);

	for (u32 i = 0; i < size; i++) {
		if (print_buffer[i] == '\n') {
			print_char('\r');
		}
		print_char(print_buffer[i]);
	}
}