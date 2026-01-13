/*
** ============================================================================
**
** FILE
**  S8051.c
**
** DESCRIPTION
**  Contains all the low level, 8051 dependent functions		    
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

#include "S8051.h"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void SetHwMasterSpi(void)
  +
  + DESCRIPTION:    initialize the HW SPI 
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void SetHwMasterSpi(void)
{
	
   SPI1CFG   = 0x40;					//Master SPI, CKPHA=0, CKPOL=0
   SPI1CN    = 0x00;					//3-wire Single Master, SPI enabled
   SPI1CKR   = (SYSCLK/(2*SPI_CLOCK))-1;
   SPI1EN 	 = 1;                     	// Enable SPI interrupt
   RF_NSEL_PIN = 1;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void delay(uint8 delay)
  +
  + DESCRIPTION:    wait  
  +
  +	INPUT:			length of the delay (1 ... 255)
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void delay_ms(uint8 delay)
{
	xdata uint8  j;
	xdata uint16 i;

	if( delay == 0 )
	{
		return;
	}

	for(j=0;j<delay;j++)
	{
		for(i=0;i<2000;i++);
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void Timer2Init(void)
  +
  + DESCRIPTION:    initialize the Timer2  
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Timer2Init(void)					//8051 Timer2 init					
{

   	CKCON &= ~0x60;                     // Timer2 uses SYSCLK/12
   	TMR2CN &= ~0x01;
  	TMR2CN = 0x04;                      // Enable Timer2 in auto-reload mode
  	                            		// Timer2 interrupt enabled
	
	TMR2L = 0x1A;							
	TMR2RLL = 0x1A;
	TMR2H = 0x0A;
	TMR2RLH = 0x0A;
	ET2 = 1;
}





/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  uint8 SpiReadWrite(uint8 data)
  +
  + DESCRIPTION:    sends and read 8 length data through the SPI port
  +
  +	INPUT:			data 
  +
  + RETURN:         received byte
  +
  + NOTES:          it doesn't control the nSEL pin
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

uint8 SpiReadWrite(uint8 spi_in)
{
	SPI1DAT = spi_in;					//write data into the SPI register
	while( SPIF1 == 0);					//wait for sending the data
	SPIF1 = 0;							//clear interrupt flag
	
	return SPI1DAT;						//read received bytes
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void SpiWriteAddressData(uint8 address, uint8 data1)
  +
  + DESCRIPTION:    sends 16 length data through the SPI port (address and data)
  +
  +	INPUT:			address - register address
  +					data 	- 8bit data 
  +
  + RETURN:         None
  +
  + NOTES:          It controls the nSEL pin
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void SpiWriteAddressData(uint8 address, uint8 data1)
{
	RF_NSEL_PIN = 0;
	SPI1DAT = address;					//write data into the SPI register
	while( SPIF1 == 0);					//wait for sending the data
	SPIF1 = 0;
	SPI1DAT = data1;					//write data into the SPI register
	while( SPIF1 == 0);					//wait for sending the data
	SPIF1 = 0;
	RF_NSEL_PIN = 1;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  uint16 SpiReadWriteWord(uint16 spi_in)
  +
  + DESCRIPTION:    sends and read 16 length data through the SPI port
  +
  +	INPUT:			data 
  +
  + RETURN:         received word
  +
  + NOTES:          it controls the nSEL pin
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


uint16 SpiReadWriteWord(uint16 spi_in)
{
	xdata uint16 temp16;

	
	RF_NSEL_PIN = 0;						
	temp16 = (uint16) (SpiReadWrite( (uint8)((spi_in & 0xFF00) >> 8) ));
	temp16 <<= 8;
	temp16 += (uint16) (SpiReadWrite( (uint8)(spi_in & 0x00FF) ));
	RF_NSEL_PIN = 1;
	

	return temp16;
}



