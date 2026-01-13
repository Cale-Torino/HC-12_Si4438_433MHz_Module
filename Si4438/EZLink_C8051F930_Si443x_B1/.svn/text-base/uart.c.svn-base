
/*
** ============================================================================
**
** FILE
**  uart.c
**
** DESCRIPTION
**  Contains all uart and buffer handle  functions
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

#include "uart.h"




/*------------------------------------------------------------------------*/
/*						GLOBAL variables								  */
/*------------------------------------------------------------------------*/
idata uint8 CircBuf[16];				//circular buffer
idata uint8 i_ptr;						//circular buffer input pointer
idata uint8 o_ptr;					//circular buffer output pointer
idata uint8 BufChar;
xdata uint8 uart_ch_sent;

extern xdata uint8 rs232_timer;




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void UartInit(void)
  +
  + DESCRIPTION:    initialize the UART peripheral
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void UartInit(void)
{

	SCON0 = 0x10;                      // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   #if (SYSCLK/BAUDRATE/2/256 < 1) 
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
   #elif (SYSCLK/BAUDRATE/2/256 < 4) 
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01
      CKCON |=  0x01;
   #elif (SYSCLK/BAUDRATE/2/256 < 12) 
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   #else 
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   #endif

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready
   ES0 = 1;                            // Enable UART0 interrupts
}


char putchar(char ch)
{
	
	
	SBUF0 = ch;
	while( uart_ch_sent == 0);
	uart_ch_sent = 0;

	return 0;	
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void UartRxISR(void)
  +
  + DESCRIPTION:    UART Receive interrupt handler
  +
  + INPUT:			None 
  +
  + RETURN:         None
  +
  + NOTES:          UartInit() has to be call before
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void UartRxISR(void)
{
	
	CircBuf[i_ptr] = SBUF0;										// get new character
	
	if(++i_ptr == CIRC_BUF_LEN) i_ptr = 0;								// buffer is circular
	if(i_ptr == o_ptr) 											// is the buffer full?
	{
		if(++o_ptr == CIRC_BUF_LEN) o_ptr = 0;					// if yes, inc output pointer
	}
	else BufChar++;
	rs232_timer = 1;
													// if not, inc Nr of characters
		
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  char ReadBuffer(void)
  +
  + DESCRIPTION:    Circular buffer read
  +
  + INPUT: 			None
  +
  + RETURN:         next character from the circular buffer
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
char ReadBuffer (void)
{
  xdata char nextChar;
  if (BufChar)                                                  // if the buffer is NOT empty:
  {
    BufChar--;                                                  // decrement the buffer
    nextChar = CircBuf[o_ptr];                                  // get the next character
    if (++o_ptr == CIRC_BUF_LEN) o_ptr = 0;                      // step to the next character
  
  	return nextChar;
  }
}







