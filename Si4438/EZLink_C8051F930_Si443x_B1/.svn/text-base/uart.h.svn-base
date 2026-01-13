/*
** ============================================================================
**
** FILE
**  uart.h
**
** DESCRIPTION
**  Header files for uart usage
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

#ifndef UART_H
#define UART_H



#include "S8051.h"


                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */


                /* ======================================= *
                 *           P A R A M E T E R S           *
                 * ======================================= */


                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

#define BAUDRATE 				(19200)			//Uart baudrate
#define CIRC_BUF_LEN			(16)				//circular buffer length
#define MESSAGE_END        (13)   			//message end <CR>

				/* ======================================= *
                 *            V A R I A B L E S            *
                 * ======================================= */


                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */

char putchar(char ch);
void UartInit(void);
void UartRxISR(void);
char ReadBuffer(void);

#endif







