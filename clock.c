// Author: strawberryhacker

#include "clock.h"
#include "registers.h"

//--------------------------------------------------------------------------------------------------

void clock_init() {
    // Disable the 8 MHz prescaler.
    SYSCTRL->OSC8M &= ~(0b11 << 8);

    // Use 1 flash wait state on 48 MHz.
    NVMCTRL->CTRLB = (NVMCTRL->CTRLB & ~(0xf << 1)) | 1 << 1;

    // Enable the PLL.
    while ((SYSCTRL->PCLKSR & (1 << 4)) == 0);
    SYSCTRL->DFLLCTRL = 0;
    while ((SYSCTRL->PCLKSR & (1 << 4)) == 0);

    // Factory programmed fuses.
    u32 coarse = (*(volatile u32 *)0x806024 >> 26) & 0x3f;
    u32 fine = (*(volatile u32 *)0x806028 >> 0) & 0x3ff;

    // Calibrate the PLL.
    SYSCTRL->DFLLVAL = coarse << 10 | fine;
    while ((SYSCTRL->PCLKSR & (1 << 4)) == 0);

    // For closed loop mode the PLL is using the USB 1kHz SOF for the synchronisation.
    SYSCTRL->DFLLCTRL |= 1 << 8 | 1 << 5;
    SYSCTRL->DFLLMUL = 1 << 26 | 1 << 16 | 48000;
    SYSCTRL->DFLLCTRL |= 1 << 2;

    // Enable the PLL.
    SYSCTRL->DFLLCTRL = 1 << 1;
    while ((SYSCTRL->PCLKSR & (1 << 4)) == 0);
    
    // Select the PLL as the input on generic clock 0.
    GCLK->GENCTRL = 1 << 16 | 1 << 17 | 7 << 8;
    while (GCLK->STATUS & (1 << 7));

    // Just enable all the clocks in the PM.
    PM->APBCMASK = 1 << 24 | 0x3f << 16 | 0xffff;
}

//--------------------------------------------------------------------------------------------------

void configure_generic_clock(u16 division, GenericSource source, u8 clock_id) {
    GCLK->GENDIV = division << 8 | clock_id;
    GCLK->GENCTRL = 1 << 16 | 1 << 17 | source << 8 | clock_id;
    while (GCLK->STATUS & (1 << 7));
}

//--------------------------------------------------------------------------------------------------

void configure_peripheral_clock(u8 peripheral_id, u8 clock_id) {
    GCLK->CLKCTRL = 1 << 14 | clock_id << 8 | peripheral_id;
    while (GCLK->STATUS & (1 << 7));
}