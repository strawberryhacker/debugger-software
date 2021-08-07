// Author: strawberryhacker

#ifndef REGISTERS_H
#define REGISTERS_H

//--------------------------------------------------------------------------------------------------

#include "utilities.h"

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u32   DIR;
	__w u32   DIRCLR;
	__w u32   DIRSET;
	__w u32   DIRTGL;
	_rw u32   OUT;
	__w u32   OUTCLR;
	__w u32   OUTSET;
	__w u32   OUTTGL;
	__r u32   IN;
	_rw u32   CTRL;
	_rw u32   WRCONFIG;
	__r u32   RESERVED0;
	_rw u8    PMUX[16];
	_rw u8    PINCFG[32];
} Port;

#define PORTA ((Port *)0x60000000)
#define PORTB ((Port *)0x60000080)

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u32   CTRLA;
	_rw u32   CTRLB;
	__r u32   RESERVED0;
	_rw u16   BAUD;
	_rw u8    RXPL;
	__r u8    RESERVED1[5];
	__w u8    INTENCLR;
	__r u8    RESERVED2;
	__w u8    INTENSET;
	__r u8    RESERVED3;
	_rw u8    INTFLAG;
	__r u8    RESERVED4;
	__w u16   STATUS;
	__r u32   SYNCBUSY;
	_rw u32   RESERVED5[2];
	_rw u16   DATA;
	__r u8    RESERVED6[6];
	_rw u8    DBGCTRL;
} Uart;

#define UART0 ((Uart *)0x42000800)
#define UART1 ((Uart *)0x42000C00)
#define UART2 ((Uart *)0x42001000)
#define UART3 ((Uart *)0x42001400)
#define UART4 ((Uart *)0x42001800)
#define UART5 ((Uart *)0x42001C00)

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u8    CTRL;
	__r u8    STATUS;
	_rw u16   CLKCTRL;
	_rw u32   GENCTRL;
	_rw u32   GENDIV;
} Gclk;

#define GCLK ((Gclk *)0x40000C00)

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u8    CTRL;
	_rw u8    SLEEP;
	__r u8    RESERVED0[6];
	_rw u8    CPUSEL;
	_rw u8    APBASEL;
	_rw u8    APBBSEL;
	_rw u8    APBCSEL;
	__r u8    RESERVED1[8];
	_rw u32   AHBMASK;
	_rw u32   APBAMASK;
	_rw u32   APBBMASK;
	_rw u32   APBCMASK;
	__r u8    RESERVED2[16];
	_rw u8    INTENCLR;
	_rw u8    INTENSET;
	_rw u8    INTFLAG;
	__r u8    RESERVED3;
	_rw u8    RCAUSE;
} Pm;

#define PM ((Pm *)0x40000400)

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u32   INTENCLR;
	_rw u32   INTENSET;
	_rw u32   INTFLAG;
	_rw u32   PCLKSR;
	_rw u16   XOSC;
	__r u8    RESERVED0[2];
	_rw u16   XOSC32K;
	__r u8    RESERVED1[2];
	_rw u32   OSC32K;
	_rw u8    OSCULP32K;
	__r u8    RESERVED2[3];
	_rw u32   OSC8M;
	_rw u16   DFLLCTRL;
	__r u8    RESERVED3[2];
	_rw u32   DFLLVAL;
	_rw u32   DFLLMUL;
	_rw u8    DFLLSYNC;
	__r u8    RESERVED4[3];
	_rw u32   BOD33;
	__r u8    RESERVED5[4];
	_rw u16   VREG;
	__r u8    RESERVED6[2];
	_rw u32   VREF;
	_rw u8    DPLLCTRLA;
	__r u8    RESERVED7[3];
	_rw u32   DPLLRATIO;
	_rw u32   DPLLCTRLB;
	_rw u8    DPLLSTATUS;
} Sysctrl;

#define SYSCTRL ((Sysctrl *)0x40000800)

//--------------------------------------------------------------------------------------------------

typedef struct {
	_rw u16   CTRLA;
	__r u16   RESERVED0;
	_rw u32   CTRLB;
	_rw u32   PARAM;
	_rw u8    INTENCLR;
	__r u8    RESERVED1[3];
	_rw u8    INTENSET;
	__r u8    RESERVED2[3];
	_rw u8    INTFLAG;
	__r u8    RESERVED3[3];
	_rw u16   STATUS;
	__r u16   RESERVED4;
	_rw u32   ADDR;
	_rw u16   LOCK;
} Nvmctrl;

#define NVMCTRL ((Nvmctrl *)0x41004000)

//--------------------------------------------------------------------------------------------------

#endif