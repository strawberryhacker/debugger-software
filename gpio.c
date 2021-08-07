// Author: strawberryhacker

#include "gpio.h"

//--------------------------------------------------------------------------------------------------

void gpio_set_function(Port* port, u32 pin, GpioFunction function) {
    port->PMUX[pin / 2] = (port->PMUX[pin / 2] & ~(0xf << (4 * (pin & 1)))) | (function << (4 * (pin & 1)));
	port->PINCFG[pin] = 1;
}

//--------------------------------------------------------------------------------------------------

void gpio_input(Port* port, u32 pin) {
    port->DIRCLR = 1 << pin;
}

//--------------------------------------------------------------------------------------------------

void gpio_output(Port* port, u32 pin) {
    port->DIRSET = 1 << pin;
}

//--------------------------------------------------------------------------------------------------

void gpio_set(Port* port, u32 pin) {
    port->OUTSET = 1 << pin;
}

//--------------------------------------------------------------------------------------------------

void gpio_clear(Port* port, u32 pin) {
    port->OUTCLR = 1 << pin;
}

//--------------------------------------------------------------------------------------------------

void gpio_toggle(Port* port, u32 pin) {
    port->OUTTGL = 1 << pin;
}