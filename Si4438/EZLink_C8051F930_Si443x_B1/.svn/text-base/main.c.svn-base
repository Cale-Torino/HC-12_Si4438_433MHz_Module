/*
** ============================================================================
**
** FILE
**  main.c
**
** DESCRIPTION
**  This is the main file of the project.	    
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


											/* ======================================================= *
											 *						INCLUDE							   *
							 				 * ======================================================= */
#include "S8051.h"
#include "uart.h"
#include "Si4432.h"
#include "EZLink_Modem_cmd.h"
											/* ======================================================= *
											 *						GLOBAL VARIABLE					   *
							 				 * ======================================================= */


extern idata uint8 BufChar;			//character counter
extern idata uint8 o_ptr;			//circular buffer output pointer
extern idata uint8 i_ptr;			//circular buffer input pointer
xdata uint8 rf_ch;					//frequency channel
xdata uint8 rf_pwr;					//RF output power
xdata uint8 rf_dr;					//datarate


xdata uint8 opmode;					//command or data mode
xdata uint8 mode;					//normal or compatible mode

xdata uint8 swit_30ms;
xdata uint8 rs232_timer;
xdata uint8 rs232_timeout;
extern xdata uint8 uart_ch_sent;



								/* ============================================================ *
								 *						Function PROTOTYPES						* 
								 * ============================================================ */
void Hw_Init(void);
INTERRUPT_PROTO (UART0_ISR, INTERRUPT_UART0);	
INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);
								/* ============================================================ *
								 *							MAIN PROGRAM						* 
								 * ============================================================ */
void main(void)															
{
	xdata uint8 packet[MAX_PAYLOAD+1], length;		//Transmit packet 
	xdata uint8 TxPacketPtr;						//Transmit packet pointer	
	


	BufChar	= 0;		
	i_ptr = 0;				
	o_ptr = 0;
	opmode = 0;				//default operation mode(command mode)
	mode = 0;				//default normal mode									
	TxPacketPtr = 0;
	rs232_timer = 0;
	rs232_timeout = 30;		//timeout 1 s
	Hw_Init();					//initialize the MCU periperals
	if( PB_PIN == 0)		//if the button pushed after reset, the demo would run in compatible mode
	{
		TR_LED_PIN = 1;
		mode = 1;
		while( PB_PIN == 0); 
		
	}
	TR_LED_PIN = 0;	

	
	printAbout();			//print the FW information to UART*/
	
	rf_pwr = 7;							//default output power
	rf_ch = 0;							//default frequency channel

	if (mode == 0)
	{	
		rf_dr = 2;							//default datarate 9.6 kbps
	}
	else 
	{
		rf_dr = 0;							//default datarate 9.6 kbps
	}

	RfInitHw();				//initialize the radio*/
	RFIdle();
	RFReceive();			//receive enable
	CMD_init();	
	while(1)														//main loop
	{

		// Synchronized routines:
        //==========================================================
        //---- 10ms soft interrupt area:
        
		 while(swit_30ms)
         {
           	--swit_30ms;
        	if(rs232_timer && rs232_timer <= rs232_timeout) ++rs232_timer;         // increase the rx timer, if it is running
         if (CMD_PIN == 1)
			{	
				opmode = 1;												//data mode
			}
			else
			{
				opmode = 0;												//command mode
			}
 	
         }
      	// NOT synchronized routines:
      	//==========================================================
		//==========================================================
	

		
	

		if (BufChar)												//if there is any char in the uart buffer
		{
			if (opmode == 0)										//command mode
			{
				CmdExec(ReadBuffer());
			}
			else													//data mode
			{

				if (TxPacketPtr < MAX_PAYLOAD)
				{
					packet[TxPacketPtr++]= ReadBuffer();				//save the received byte
				}

				if ((TxPacketPtr >= MAX_PAYLOAD)||(packet[TxPacketPtr-1] == MESSAGE_END))
				{
					TR_LED_PIN = 1;
					RFIdle();
					TxFIFOReset();
					RFTransmit(&packet[0],TxPacketPtr);
					TxPacketPtr = 0;
					rs232_timer = 0;
					TR_LED_PIN = 0;
					RFIdle();
					RxFIFOReset();
					RFReceive();				//enable the receiver chain again
				}
			}	
		}	
		
		if(opmode == 1)
		{
			if(rs232_timer > rs232_timeout)
			{
				TR_LED_PIN = 1;
				RFIdle();
				TxFIFOReset();
				RFTransmit(&packet[0],TxPacketPtr);
				TxPacketPtr = 0;
				rs232_timer = 0;
				TR_LED_PIN = 0;
				RFIdle();
				RxFIFOReset();
				RFReceive();				//enable the receiver chain again
			}
		
		}	
							/* ================================================== */
							/* 				Linktest button pressed				  */
							/* ================================================== */	
	
		switch( RFPacketReceived(&packet[0], &length) )
		{
				case RF_PACKET_RECEIVED:
					//blink RX LED
					RC_LED_PIN = 1;
					//print packet content
					packet[length] = 0;
					printf("%s", &packet[0]);
					//wait a bit for showing the LED a bit longer
					delay_ms(50);
					//release RX LED
					RC_LED_PIN = 0;
					//check whether ACK needs to be sent or not
					if( memcmp(&packet[0], "Link ??", 7) == 0 )
					{
						//send ACK
						TR_LED_PIN = 1;
						//send a packet
						length = 9;
						strcpy(&packet[0],"Link OK\r\n");
						RFIdle();
						TxFIFOReset();
						RFTransmit(&packet[0],length);
						//wait a bit for showing the LED a bit longer
						delay_ms(50);
						//releaze the LED
						TR_LED_PIN = 0;
					}
				
					RFIdle();
					RxFIFOReset();
					RFReceive();
				break;

				case RF_NO_PACKET:
					if( PB_PIN == 0 )
					{//push button is pressed -> send a packet
						//wait for releaze the button
						while(PB_PIN == 0);
						//blink the LED
						TR_LED_PIN = 1;
						//send a packet
						length = 9;
						strcpy(&packet[0],"Link ??\r\n");
						RFIdle();
						TxFIFOReset();
						RFTransmit(&packet[0],length);
						//wait a bit for showing the LED a bit longer
						delay_ms(50);
						//releaze the LED
						TR_LED_PIN = 0;
						//start receiving
						RFIdle();
						RxFIFOReset();
						RFReceive();
					}
				break;

				case RF_CRC_ERROR:
				default:
					//restart RX
					RFIdle();
					RxFIFOReset();
					RFReceive();
				break;
		}

	}
}


								/* ================================================ */
								/*						UART0 ISR					*/
								/* ================================================ */

INTERRUPT(UART0_ISR, INTERRUPT_UART0) 
{

	if( RI0 == 1 )													//check RX interrupt
	{
		
		
		UartRxISR();												//call the UART RX interrupt handler
		RI0 = 0;													//clear IT Flag
	}
	
	if( TI0 == 1)
	{
		uart_ch_sent = 1;
		TI0 = 0;
	}
	
}


INTERRUPT(TIMER2_ISR, INTERRUPT_TIMER2)
{

	++swit_30ms;  
	TF2H = 0;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void Init(void)
  +
  + DESCRIPTION:    This function configures the HW  
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Hw_Init(void)
{
	DisableGlobalIt(); 
    /*Disable the Watchdog Timer*/
	PCA0MD &= ~0x40;                    
   PCA0MD = 0x00;
								// Disable interrupts 
	
	/* Internal Oscillator SYSCLK  (24.5 MHz)*/
	OSCICN    = 0x8F;
   FLSCL     = 0x40;
   CLKSEL    = 0x00;
	
	/*Initialize I/O ports*/
	P0MDIN    = 0xFF;					
   P1MDIN    = 0xFF;  
	P2MDIN	  = 0xFF;
	P0MDOUT   = 0x12;
	P1MDOUT   = 0x4D;						
   P2MDOUT   = 0x01;


	P0     	  |= 0xE0;                      //Set P0 inputs
	P1		  |= 0x12;						//Set P1 inputs

 
      	
	SFRPAGE  = 0x0F;
	P0DRV	  	= 0x12;	
   P1DRV    = 0x4D;
   P2DRV    = 0x01;
    
	SFRPAGE  = 0x00;
	XBR0     = 0x01;
   XBR1     = 0x40;
   XBR2     = 0x40;


	
	//Initialize SPI
	SetHwMasterSpi();
	//Initialize Uart
	UartInit();
	//Initialize Timer2
	Timer2Init();
		
	TR_LED_PIN = 1;
	delay_ms(5);
	RC_LED_PIN = 1;
	delay_ms(5);
	TR_LED_PIN = 0;
	delay_ms(5);
	RC_LED_PIN = 0;
	
	EnableGlobalIt();
}
