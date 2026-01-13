/*
** ============================================================================
**
** FILE
**  Si4432.c
**
** DESCRIPTION
**  Contains all Si4432 RF functions		    
**
** CREATED
**  Silicon Laboratories Hungary Ltd
**
** COPYRIGHT
**  Copyright 2009 Silicon Laboratories, Inc.  
**	http://www.silabs.com
**
** ============================================================================
*/

#include "S8051.h"
#include "Si4432.h"
#include "uart.h"




/*------------------------------------------------------------------------*/
/*						GLOBAL variables								  */
/*------------------------------------------------------------------------*/
code uint8 RMRfSettings[NMBR_OF_SAMPLE_SETTING1][NMBR_OF_PARAMETER] =		
{
//revB1
//	 IFBW, COSR, CRO2, CRO1, CRO0, CTG1, CTG0, TDR1, TDR0, MMC1, FDEV,	AFC,	AFCTimingControl, AFCLimiter	
	{0x1D, 0x41, 0x60, 0x27, 0x52, 0x00, 0x05, 0x13, 0xa9, 0x20, 0x3a,  	0x40, 0x0A,					0x20}, 	//DR: 2.4kbps, DEV: +-36kHz, BBBW: 75.2kHz (crystal:20 ppm)
	{0x1D, 0xA1, 0x20, 0x4E, 0xA5, 0x00, 0x0A, 0x27, 0x52, 0x20, 0x48, 	0x40,	0x0A,					0x20},	//DR: 4.8kbps, DEV: +-45kHz, BBBW: 95.3kHz (crystal:20 ppm)
	{0x1E, 0xD0, 0x00, 0x9D, 0x49, 0x00, 0x24, 0x4e, 0xa5, 0x20, 0x48, 	0x40,	0x0A,					0x20},	//DR: 9.6kbps, DEV: +-45kHz, BBBW: 112.8kHz (crystal:20 ppm)
	{0x03, 0xD0, 0x00, 0x9D, 0x49, 0x01, 0x3D, 0x9D, 0x49, 0x20, 0x0F,	0x40,	0x0A,					0x1E},	//DR: 19.2kbps, DEV: +-9.6kHz, BBBW: 75.2kHz (crystal:20 ppm)
	{0x03, 0x68, 0x01, 0x3A, 0x93, 0x02, 0x78, 0x09, 0xD5, 0x00, 0x1F,	0x40,	0x0A,					0x20},	//DR: 38.4kbps, DEV: +-19.2kHz, BBBW: 83.2kHz (crystal:20 ppm)  
	{0x06, 0x45, 0x01, 0xD7, 0xDC, 0x03, 0xB8, 0x0E, 0xBF, 0x00, 0x2E,	0x40,	0x0A,					0x2D},	//DR: 57.6kbps, DEV: +-28.8kHz, BBBW: 124.6kHz (crystal:20 ppm)
	{0x82, 0x68, 0x01, 0x3A, 0x93, 0x02, 0x78, 0x1D, 0x7E, 0x00, 0x5C,	0x40,	0x0A,					0x50},	//DR: 115.2kbps, DEV: +-57.6kHz, BBBW: 172.8kHz (crystal:20 ppm)

};

code uint8 CMRfSettings[NMBR_OF_SAMPLE_SETTING2][NMBR_OF_PARAMETER] =		
{
//revB1
//	 IFBW, COSR, CRO2, CRO1, CRO0, CTG1, CTG0, TDR1, TDR0, MMC1, FDEV,	AFC, 	AFCTimingControl, AFCLimiter
	{0x9A, 0x71, 0x40, 0x34, 0x6E, 0x00, 0x08, 0x4e, 0x79, 0x20, 0x90,	0x40,	0x0A,					0x41},	//DR: 9.6kbps, DEV: +-90kHz, BBBW:208.4kHz (crystal: 20ppm)
	
};

#ifdef BAND_434
//parameters of the frequency setting
	code uint8 FreqSettings[4][7] =		
	{

	//	 2.4kbps,	4.8kbps,	9.6kbps, 	19.2kbps,	38.4kbps 	57.6kbps 	115.2kbps 
		{4,			4,			4, 			3, 			3, 			2, 			1 	  }, 			//max channel number  
		{0x53,		0x53,		0x53, 		0x58, 		0x56, 		0x5A, 		0x61 },			//start freq. reg1
		{0x40,		0x40,		0x40, 		0x40, 		0xC0, 		0x40, 		0xC0 },			//start freq. reg2 
		{33,			33,		33,	 		39, 			45, 			36, 			0 	  },			//freq. step   

	};
#endif

#ifdef BAND_470
//parameters of the frequency setting
	code uint8 FreqSettings[4][7] =		
	{

	//	 2.4kbps,	4.8kbps,	9.6kbps, 	19.2kbps,	38.4kbps 	57.6kbps 	115.2kbps 
		{39,			39,		39, 			39, 			39, 			39, 			39	  }, 			//max channel number  
		{0x19,		0x19,		0x19, 		0x19, 		0x19, 		0x19, 		0x19 },			//start freq. reg1
		{0x00,		0x00,		0x00, 		0x00, 		0x00, 		0x00, 		0x00 },			//start freq. reg2 
		{100,			100,		100,	 		100, 			100, 			100, 			100  },			//freq. step   

	};
#endif

#ifdef BAND_868
	//parameters of the frequency setting
	code uint8 FreqSettings[4][7] =		
	{

	//	 2.4kbps,	4.8kbps,	9.6kbps, 	19.2kbps,	38.4kbps 	57.6kbps 	115.2kbps 
		{14,			14,		14,	 		11, 			10, 			8, 			6    },  			//max channel number  
		{0x2C,		0x2C,		0x2C, 		0x2E, 		0x2D, 		0x2E, 		0x32 },				//start freq. reg1
		{0x60,		0x60,		0x60, 		0x40, 		0x40, 		0xE0, 		0x00 },				//start freq. reg2
		{45,			45,		45,	 		55, 			64, 			78, 			100  },				//freq. step   

	};
#endif

#ifdef BAND_915
 	//parameters of the frequency setting
	code uint8 FreqSettings[4][7] =		
	{

	//	 2.4kbps,	4.8kbps,	9.6kbps, 	19.2kbps,	38.4kbps 	57.6kbps 	115.2kbps 
		{60,			60,		60, 			52, 			45, 			37, 			29  },	  			//max channel number  
		{0x0A,		0x0A,		0x0A, 		0x0A, 		0x0A, 		0x0A, 		0x0A},				//start freq. reg1 
		{0x80,		0x80,		0x80, 		0x80, 		0x80, 		0x80, 		0x80},				//start freq. reg2 
		{48,			48,		48, 			55, 			64, 			78, 			100 },				//freq. step   

	};
#endif

#ifdef BAND_950
 	//parameters of the frequency setting
	code uint8 FreqSettings[4][7] =		
	{

	//	 2.4kbps,	4.8kbps,	9.6kbps, 	19.2kbps,	38.4kbps 	57.6kbps 	115.2kbps 
		{24,			24,		24, 			24, 			24, 			24, 			12  },	  			//max channel number  
		{0x8A,		0x8A,		0x8A, 		0x8A, 		0x8A, 		0x8A, 		0x8A},				//start freq. reg1 
		{0xC0,		0xC0,		0xC0, 		0xC0, 		0xC0, 		0xC0, 		0xC0},				//start freq. reg2 
		{20,			20,		20, 			20, 			20, 			40, 			40  },				//freq. step   

	};
#endif


extern xdata uint8 rf_ch;
extern xdata uint8 rf_pwr;
extern xdata uint8 rf_dr;
extern xdata uint8 mode;




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  	void RfInitHw(void)
  +
  + DESCRIPTION:    	initializes the used I/O pins, SPI and timer peripherals, 
  +						IT routines needed for the RF stack
  +
  + RETURN:         	None
  +
  + NOTES:	         1.) has to be called in the power-on routine
  +					
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RfInitHw(void)
{

	xdata uint8 i;
	xdata uint16 j;

   //initialize I/O port directions
  	RF_NSEL_PIN    = 1;
   RF_PWRDN_PIN   = 0;

	//After set the RF_PWRDN_PIN to zero, need some time to wait ( ~15 ms)
	for(i=0;i<15;i++)
		for(j=0;j<35000;j++);

	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);
   
	//SW reset  
   SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x80);

	//wait until the POR interrupt is occured
	while(RF_NIRQ_PIN == 1);
  	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);

	//wait until the chip ready interrupt is occured
	while(RF_NIRQ_PIN == 1);
  	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);

	//disable all the interrupts
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x00);
   SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x02); 

 	//set  cap. bank  
	SpiWriteAddressData((REG_WRITE | CrystalOscillatorLoadCapacitance), 0x6D);

 	//reset digital testbus, disable scan test
   SpiWriteAddressData((REG_WRITE | DigitalTestBus), 0x00);      
   //select nothing to the Analog Testbus
   SpiWriteAddressData((REG_WRITE | AnalogTestBus), 0x0B);
   	   
	//set frequency
	SpiWriteAddressData((REG_WRITE | FrequencyBandSelect), FREQ_BAND_SELECT);                  
	set_frq(rf_ch);	
	      
   //disable RX-TX headers, 
   SpiWriteAddressData((REG_WRITE | HeaderControl1), 0x00 );            
   SpiWriteAddressData((REG_WRITE | HeaderControl2), 0x02 );    
	SpiWriteAddressData((REG_WRITE | SyncWord3), 0x2D);
	SpiWriteAddressData((REG_WRITE | SyncWord2), 0xD4);
   
	//enable packet handler( no CRC ) 
	SpiWriteAddressData((REG_WRITE | DataAccessControl), 0x88);
	//set GFSK modulation and FIFO mode
	SpiWriteAddressData((REG_WRITE | ModulationModeControl2), 0x63);
	
	//set preamble length & detection threshold
	SpiWriteAddressData((REG_WRITE | PreambleLength), (PREAMBLE_LENGTH << 1));		
	SpiWriteAddressData((REG_WRITE | PreambleDetectionControl), (( PD_LENGTH << 4)|0x02));
	
	     
   //set GPIO0 to GND
   SpiWriteAddressData((REG_WRITE | GPIO0Configuration), 0x14);
   //set GPIO1 & GPIO2 to control the TRX switch
   SpiWriteAddressData((REG_WRITE | GPIO1Configuration), 0x12);
	SpiWriteAddressData((REG_WRITE | GPIO2Configuration), 0x15);
	
	set_pwr(rf_pwr);
	RFSetRfParameters(rf_dr);				
	
		
	return RF_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFSetRfParameters(RF_SAMPLE_SETTINGS setting)
  +
  + DESCRIPTION:    	this function configures the RF part of the chip (both TX and RX)
  + 						for different (predefined) data rate, deviation and modulation index 
  +						requirements.
  +					
  +
  + RETURN:         RF_OK: 				the operation was succesfull
  +                 RF_ERROR_PARAMETER: invalid parameter, the operation is ignored.
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RFSetRfParameters(RF_SAMPLE_SETTINGS setting)
{
		
	if (mode == 0)
	{	
		//set the registers according the selected RF settings in the range mode
		SpiWriteAddressData((REG_WRITE | IFFilterBandwidth), RMRfSettings[setting][0] );
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOversamplingRatio), RMRfSettings[setting][1]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset2), RMRfSettings[setting][2]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset1), RMRfSettings[setting][3]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset0), RMRfSettings[setting][4]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain1), RMRfSettings[setting][5]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain0), RMRfSettings[setting][6]);
		SpiWriteAddressData((REG_WRITE | TXDataRate1), RMRfSettings[setting][7]);
		SpiWriteAddressData((REG_WRITE | TXDataRate0), RMRfSettings[setting][8]);
		SpiWriteAddressData((REG_WRITE | ModulationModeControl1), RMRfSettings[setting][9]);
		SpiWriteAddressData((REG_WRITE | FrequencyDeviation), RMRfSettings[setting][10]); 
		SpiWriteAddressData((REG_WRITE | AFCLoopGearshiftOverride), RMRfSettings[setting][11]);
		SpiWriteAddressData((REG_WRITE | AFCTimingControl), RMRfSettings[setting][12]);
		SpiWriteAddressData((REG_WRITE | AFCLimiter), RMRfSettings[setting][13]);

	}
	else
	{	
		//set the registers according the selected RF settings in the compatible mode 
		SpiWriteAddressData((REG_WRITE | IFFilterBandwidth), CMRfSettings[setting][0] );
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOversamplingRatio), CMRfSettings[setting][1]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset2), CMRfSettings[setting][2]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset1), CMRfSettings[setting][3]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryOffset0), CMRfSettings[setting][4]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain1), CMRfSettings[setting][5]);
		SpiWriteAddressData((REG_WRITE | ClockRecoveryTimingLoopGain0), CMRfSettings[setting][6]);
		SpiWriteAddressData((REG_WRITE | TXDataRate1), CMRfSettings[setting][7]);
		SpiWriteAddressData((REG_WRITE | TXDataRate0), CMRfSettings[setting][8]);
		SpiWriteAddressData((REG_WRITE | ModulationModeControl1), CMRfSettings[setting][9]);
		SpiWriteAddressData((REG_WRITE | FrequencyDeviation), CMRfSettings[setting][10]);	
		SpiWriteAddressData((REG_WRITE | AFCLoopGearshiftOverride), CMRfSettings[setting][11]);
		SpiWriteAddressData((REG_WRITE | AFCTimingControl), CMRfSettings[setting][12]);
		SpiWriteAddressData((REG_WRITE | AFCLimiter), CMRfSettings[setting][13]);

	}

	
	
		
	return RF_OK;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFIdle(void)
  +
  + DESCRIPTION:    sets the transceiver and the RF stack into IDLE state, 
  +					independently of the actual state of the RF stack.
  +
  + RETURN:         RF_OK: 			the operation was succesfull
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RFIdle(void)
{
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x01);

	//diasble all ITs
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x00);
	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00);

	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);


	return RF_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFTransmit(uint8 * packet, uint8 length)
  +
  + DESCRIPTION:    starts packet transmission
  +
  + INPUT:			MESSAGE structure
  +
  + RETURN:         RF_OK: 				the packet sent correctly
  +					RF_ERROR_TIMING: 	timing poblem -> the packet didn't send within timeout
  +					RF_ERROR_PARAMETER: the command is ignored, some of the 
  +										input parameter(s) are
  +										out of the valid range
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

RF_ENUM RFTransmit(uint8 * packet, uint8 length)
{
	xdata uint8 temp8;
	
	//set packet content
	SpiWriteAddressData((REG_WRITE | TransmitPacketLength), length);					
	for(temp8=0;temp8<length;temp8++)
	{
		SpiWriteAddressData((REG_WRITE | FIFOAccess),packet[temp8]);		
	}
	
	//enable the wanted ITs
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x04);
	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00);

	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);
	//enable transmitter
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x09);
	
	while(RF_NIRQ_PIN == 1);

	return RF_OK;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFReceive(void)
  +
  + DESCRIPTION:    starts packet reception
  +
  + INPUT:			None
  +
  + RETURN:         RF_OK: 				the operation was succesfull
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RFReceive(void)
{
	
	//enable the packet valid interrupt
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x02); 
 	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00); 
	
	SpiReadWriteWord(InterruptStatus1 << 8);
	SpiReadWriteWord(InterruptStatus2 << 8);

	//enable receiver chain
   SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x05);

	return RF_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RFPacketReceived(uint8 * packet, uint8 * length)
  +
  + DESCRIPTION:    check wheter the packet received or not.
  +
  + INPUT:			pointers for storing data and length
  +
  + RETURN:         RF_PACKET_RECEIVED:		packet received
  +					RF_NO_PACKET:			packet is not yet received
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RFPacketReceived(uint8 * packet, uint8 * length)
{
	xdata uint8 i;

	if( RF_NIRQ_PIN == 0 )
	{
		
		i = (uint8)(0x00FF & SpiReadWriteWord(InterruptStatus1 << 8));
			
		if( (i & 0x01) == 0x01 )
		{//CRC error
			//disable receiver 
			SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x01);
			return RF_CRC_ERROR;
		}
		if( (i & 0x02) == 0x02 )
		{//packet received
			//read buffer
			*length =  (uint8)(0x00FF & SpiReadWriteWord(ReceivedPacketLength << 8)) ;
			for(i=0;i<*length;i++)
			{
				*packet++ = (uint8)(0x00FF & SpiReadWriteWord(FIFOAccess << 8));
			}
			//disable receiver 
			SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x01);
			return RF_PACKET_RECEIVED;
		}
	}
	
	return RF_NO_PACKET;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void RFCWTest(void)
  +
  + DESCRIPTION:    set the chip into CW mode
  +
  + INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void RFCWTest(void)
{
	
	
	//enable CW mode
	SpiWriteAddressData((REG_WRITE | ModulationModeControl2), 0x00);
	//disable packet handler & CRC16
	SpiWriteAddressData((REG_WRITE | DataAccessControl), 0x00);
	//enable transmitter
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl1), 0x09);
	//disable all the ITs
	SpiWriteAddressData((REG_WRITE | InterruptEnable1), 0x00);
	SpiWriteAddressData((REG_WRITE | InterruptEnable2), 0x00);
	//set GPIO0 to RX_DATA
	SpiWriteAddressData((REG_WRITE | GPIO0Configuration), 0x14);
	//set GPIO1 & GPIO2 to control the TRX switch
	SpiWriteAddressData((REG_WRITE | GPIO1Configuration), 0x12);
	SpiWriteAddressData((REG_WRITE | GPIO2Configuration), 0x15);
	TR_LED_PIN = 1;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM RxFIFOReset(void)
  +
  + DESCRIPTION:    reset the RX FIFO after receiving
  +
  + INPUT:			  None  
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM RxFIFOReset(void)
{
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x02);
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x00);

	return RF_OK;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM TxFIFOReset(void)
  +
  + DESCRIPTION:    reset the TX FIFO before transmitting
  +
  + INPUT:			  None  
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM TxFIFOReset(void)
{
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x01);
	SpiWriteAddressData((REG_WRITE | OperatingFunctionControl2), 0x00);

	return RF_OK;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM set_dr(RF_SAMPLE_SETTINGS setting)
  +
  + DESCRIPTION:    set the datarate 
  +
  + INPUT:			the number of the modem parameter settings  
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
RF_ENUM set_dr(RF_SAMPLE_SETTINGS setting)
{

	//set the registers according the selected RF settings
	
   RFSetRfParameters(setting);

	return RF_OK;

}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM set_pwr(uint8 pwr)
  +
  + DESCRIPTION:    set the TX power 
  +
  + INPUT:			TXPower register content   
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

RF_ENUM set_pwr(uint8 pwr)
{

	SpiWriteAddressData((REG_WRITE | TXPower), (pwr|0x18));

	return RF_OK;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  RF_ENUM set_frq(uint8 frq)
  +
  + DESCRIPTION:    set the TX frequency   
  +
  + INPUT:			the number of the frequency channel  
  +
  + RETURN:         None
  +
  + NOTES:          
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

RF_ENUM set_frq(uint8 frq)
{
	//set frequency
	SpiWriteAddressData((REG_WRITE | NominalCarrierFrequency1), FreqSettings[1][rf_dr] );
	SpiWriteAddressData((REG_WRITE | NominalCarrierFrequency0), FreqSettings[2][rf_dr] );
	SpiWriteAddressData((REG_WRITE | FrequencyHoppingStepSize), FreqSettings[3][rf_dr] );
	SpiWriteAddressData((REG_WRITE | FrequencyHoppingChannelSelect), frq);
	
	return RF_OK;
}