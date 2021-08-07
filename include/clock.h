// Author: strawberryhacker

#ifndef CLOCK_H
#define CLOCK_H

#include "utilities.h"

//--------------------------------------------------------------------------------------------------

typedef enum {
    GENERIC_SOURCE_XOSC,
    GENERIC_SOURCE_GCLKIN,
    GENERIC_SOURCE_GCLKGEN1,
    GENERIC_SOURCE_OSCULP32K,
    GENERIC_SOURCE_OSC32K,
    GENERIC_SOURCE_XOSC32K,
    GENERIC_SOURCE_OSC8M,
    GENERIC_SOURCE_DFLL4M,
    GENERIC_SOURCE_FDPLL96M,
} GenericSource;

//--------------------------------------------------------------------------------------------------

void clock_init();
void configure_generic_clock(u16 division, GenericSource source, u8 clock_id);
void configure_peripheral_clock(u8 peripheral_id, u8 clock_id);

#endif