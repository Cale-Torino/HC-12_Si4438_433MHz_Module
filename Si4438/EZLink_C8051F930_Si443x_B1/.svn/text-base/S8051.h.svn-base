/*
** ============================================================================
**
** FILE
**  S8051.h
**
** DESCRIPTION
**  This file contains all the 8051 definitions
**
** CREATED
**  Silicon Laboratories Hungary Ltd
**
** COPYRIGHT
**  Copyright 2008 Silicon Laboratories, Inc.  
**	http://www.silabs.com
**
** ============================================================================
*/


#ifndef S8051_H
#define S8051_H

#include <compiler_defs.h>             // compiler declarations
#include <C8051F930_defs.h>
#include <string.h>
#include <stdio.h>
#include "global_definitions.h"

                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */

//Only these type of variables are used in this software
#undef	uint8
#undef	sint8
#undef	uint16
#undef	sint16
#undef	uint32
#undef	sint32

#define	uint8	unsigned char
#define	sint8	signed char
#define	uint16	unsigned short
#define	sint16	signed short
#define	uint32	unsigned long
#define	sint32	signed long



					                /* ======================================= *
					                 *          D E F I N I T I O N S          *
					                 * ======================================= */
#undef	TRUE
#undef 	FALSE
#undef	INPUT
#undef	OUTPUT

#define TRUE						(1)
#define FALSE						(0)
#define	INPUT						(1)
#define	OUTPUT						(0)


								/*8051 clock definitions*/
#define SYSCLK       			(24500000)        	// SYSCLK frequency in Hz
#define	SPI_CLOCK				(4083332)		

								/*I/O port definitions*/

SBIT (RF_NSEL_PIN,	SFR_P1, 3);
SBIT (RF_NIRQ_PIN,	SFR_P0, 6);
SBIT (RF_PWRDN_PIN,	SFR_P0, 1);

SBIT (SPI_MISO, 	SFR_P1, 1);
SBIT (SPI_MOSI, 	SFR_P1, 2);

SBIT (RC_LED_PIN,  	SFR_P2, 0);      // '0' means ON, '1' means OFF
SBIT (TR_LED_PIN,	SFR_P1, 6);      // '0' means ON, '1' means OFF
SBIT (PB_PIN,       SFR_P0, 7);      // PB == 0 means switch pressed
SBIT (CMD_PIN,		SFR_P1, 4);	


								/* MACROS */
#define	EnableGlobalIt()		EA = 1
#define	DisableGlobalIt()		EA = 0



								
               				/* ======================================= *
                 			 *  F U N C T I O N   P R O T O T Y P E S  *
                			 * ======================================= */


void SetHwMasterSpi(void);
void Timer2Init(void);
uint8 SpiReadWrite(uint8 spi_in);
void SpiWriteAddressData(uint8 address, uint8 data1);
uint16 SpiReadWriteWord(uint16 spi_in);
void delay_ms(uint8 delay);


#endif 


