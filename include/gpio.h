// Author: strawberryhacker

#ifndef GPIO_H
#define GPIO_H

#include "utilities.h"
#include "registers.h"

//--------------------------------------------------------------------------------------------------

typedef enum {
    GPIO_FUNCTION_A,
    GPIO_FUNCTION_B,
    GPIO_FUNCTION_C,
    GPIO_FUNCTION_D,
    GPIO_FUNCTION_E,
    GPIO_FUNCTION_F,
    GPIO_FUNCTION_G,
    GPIO_FUNCTION_H,
    GPIO_FUNCTION_I,
    GPIO_FUNCTION_J,
} GpioFunction;

//--------------------------------------------------------------------------------------------------

void gpio_init(Port* port, u32 pin);
void gpio_set_function(Port* port, u32 pin, GpioFunction function);
void gpio_input(Port* port, u32 pin);
void gpio_output(Port* port, u32 pin);
void gpio_set(Port* port, u32 pin);
void gpio_clear(Port* port, u32 pin);
void gpio_toggle(Port* port, u32 pin);

#endif