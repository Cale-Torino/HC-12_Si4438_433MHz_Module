/*
/*
** ============================================================================
**
** FILE
**  EZLink_Modem_cmd.c
**
** DESCRIPTION
**  Contains all modem functions		    
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

//===============================================================================================
// Radio modem
// ASCIII command interpreter
//===============================================================================================
#include "S8051.h"
#include "EZLink_Modem_cmd.h"
#include "uart.h"
#include "Si4432.h"


						/* =========================================================== *
						 *						GLOBAL variables					   *
						 * =========================================================== */


extern xdata uint8 rf_ch;		//frequency channel
extern xdata uint8 rf_pwr;		//RF output power
extern xdata uint8 rf_dr;		//datarate

extern xdata uint8 mode;
extern code uint8 FreqSettings[4][7];

xdata uint8 cis;           				 // CMD interpreter status
xdata uint8 iparam;         				// command parameter, 0-255


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void CM_init(void)
  +
  + DESCRIPTION:    initialize the character interpreter statemachine
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void CMD_init(void)
{
  cis = 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void printAbout(void)
  +
  + DESCRIPTION:    print the firmware information to UART
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void printAbout(void)
{
	if ( mode == 0 ) 
	{	
		printf("SRW005,");
		printf(HW_VERSION);
		printf(",");
		printf(FW_VERSION);
		printf(",ED\r\n");
		printf("EZLink demo ");
		printf(BAND);
		printf("MHz\r\n");
  		printf("Silicon Laboratories, 2010\r\n");
		printf("www.silabs.com\r\n");
  	}
	else
	{
		printf("SRW005,");
		printf(HW_VERSION);
		printf(",");
		printf(FW_VERSION);
		printf(",ED\r\n");
		printf("EZLink demo ");
		printf(BAND);
		printf("MHz\r\n");
		printf("Si4421 compatible mode\r\n");
		printf("Silicon Laboratories, 2010\r\n");
		printf("www.silabs.com\r\n");



	}
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void printOK(void)
  +
  + DESCRIPTION:    print OK to UART
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void printOK(void)
{
  printf("\n\rOK\n\r>\n\r");
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void printHelp(void)
  +
  + DESCRIPTION:    print help information to UART
  +
  +	INPUT:			None
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void printHelp(void)
{
  if ( mode ==  0)
  {
	  printf("\n\rF=n : Set the rf channel");
	  #ifdef  BAND_434  
	  printf("\n\r 	2.4 kbps; channel number:0-3");
	  printf("\n\r 	4.8 kbps; channel number:0-3");
	  printf("\n\r 	9.6 kbps; channel number:0-3");
	  printf("\n\r 	19.2 kbps; channel number:0-2");
	  printf("\n\r 	38.4 kbps; channel number:0-2");
	  printf("\n\r 	57.6 kbps; channel number:0-1");
	  printf("\n\r 	115.2 kbps; channel number:0");
	  #endif
  	  #ifdef  BAND_470  
	  printf("\n\r 	2.4 kbps; channel number:0-38");
	  printf("\n\r 	4.8 kbps; channel number:0-38");
	  printf("\n\r 	9.6 kbps; channel number:0-38");
	  printf("\n\r 	19.2 kbps; channel number:0-38");
	  printf("\n\r 	38.4 kbps; channel number:0-38");
	  printf("\n\r 	57.6 kbps; channel number:0-38");
	  printf("\n\r 	115.2 kbps; channel number:0-38");
	  #endif
     #ifdef  BAND_868
	  printf("\n\r 	2.4 kbps; channel number:0-13");
	  printf("\n\r 	4.8 kbps; channel number:0-13");
	  printf("\n\r 	9.6 kbps; channel number:0-13");
	  printf("\n\r 	19.2 kbps; channel number:0-10");
	  printf("\n\r 	38.4 kbps; channel number:0-9");
	  printf("\n\r 	57.6 kbps; channel number:0-7");
	  printf("\n\r 	115.2 kbps; channel number:0-5");
	  #endif
	  #ifdef  BAND_915
	  printf("\n\r 	2.4 kbps; channel number:0-59");
	  printf("\n\r 	4.8 kbps; channel number:0-59");
	  printf("\n\r 	9.6 kbps; channel number:0-59");
	  printf("\n\r 	19.2 kbps; channel number:0-51");
	  printf("\n\r 	38.4 kbps; channel number:0-44");
	  printf("\n\r 	57.6 kbps; channel number:0-36");
	  printf("\n\r 	115.2 kbps; channel number:0-28"); 
	  #endif
  	  #ifdef  BAND_950
	  printf("\n\r 	2.4 kbps; channel number:0-23");
	  printf("\n\r 	4.8 kbps; channel number:0-23");
	  printf("\n\r 	9.6 kbps; channel number:0-23");
	  printf("\n\r 	19.2 kbps; channel number:0-23");
	  printf("\n\r 	38.4 kbps; channel number:0-23");
	  printf("\n\r 	57.6 kbps; channel number:0-23");
	  printf("\n\r 	115.2 kbps; channel number:0-11"); 
	  #endif
	  printf("\n\rD=n : Set the rf datarate (0 - 6)");
	  printf("\n\r	0 - DR: 2.4kbps, DEV: +-36kHz, BBBW: 75.2kHz");
	  printf("\n\r	1 - DR: 4.8kbps, DEV: +-45kHz, BBBW: 95.3kHz");
	  printf("\n\r	2 - DR: 9.6kbps, DEV: +-45kHz, BBBW: 99.6kHz");
	  printf("\n\r	3 - DR: 19.2kbps, DEV: +-9.6kHz, BBBW: 28.8kHz");	
	  printf("\n\r	4 - DR: 38.4kbps, DEV: +-19.2kHz, BBBW: 57.6kHz");
	  printf("\n\r	5 - DR: 57.6kbps, DEV: +-28.8kHz, BBBW: 86.4kHz"); 
	  printf("\n\r	6 - DR: 115.2kbps, DEV: +-57.6kHz, BBBW: 172.8kHz");
	  printf("\n\rP=n : Set the rf output power");
	  printf("\n\r      Si4431: 0-7 (-8dBm,-5dBm,-2dBm,+1dBm,+4dBm,+7dBm,+10dBm,+13dBm)");
  	  printf("\n\r      Si4432: 0-7 (+1dBm,+2dBm,+5dBm,+8dBm,+11dBm,+14dBm,+17dBm,+20dBm)");
	  printf("\n\rS?  : Print the current settings");
	  printf("\n\rI   : Print firmware version information");
	  printOK();
  }
  else
  {
	  printf("\n\rF=n : Set the rf channel");
	  #ifdef BAND_434  
	  printf("(0-3)");
	  #endif
  	  #ifdef BAND_470  
	  printf("(0-38)");
	  #endif
	  #ifdef BAND_868
	  printf("(0-13)");
	  #endif
	  #ifdef BAND_915 
	  printf("(0-59)");
	  #endif
	  #ifdef BAND_950
	  printf("(0-23)");		  
	  #endif
	  	
	  printf("\n\rRF parameters:");
	  printf("\n\r	DR: 9.6kbps, DEV: +-90kHz, BBBW:184.8kHz");
	  printf("\n\rP=n : Set the rf output power (0 - 3; +11dBm, +14dBm, +17dBm, +20dBm)");
	  printf("\n\rS?  : Print the current settings");
	  printf("\n\rI   : Print firmware version information");
	  printOK();
  }
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void CmdExec(char CMD)
  +
  + DESCRIPTION:    CMD character interpreter
  +
  +	INPUT:			CMD - received character form UART
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void CmdExec(uint8 CMD)         
                                 // CMD character interpreter
{

  if ((CMD != '\n') && (CMD != ' '))                            // don't use <space> and <LF>
  switch (cis)                                                  // cis: Command Interpreter Status
    {
    case 0:                                                     // cis=0: basic state
      switch (CMD)
        {
        case '\r':
          printOK();
          break;
        case '?':
          cis = 1;
          break;
        case 'I': case 'i':
          cis = 2;
          break;
        case 'S': case 's':
          cis = 3;
          break;
        case 'F': case 'f':
          cis = 10;
          iparam = 0;
          break;
        case 'D': case 'd':
          cis = 20;
          iparam = 0;
          break;
        case 'P': case 'p':
          cis = 30;
          iparam = 0;
          break;
		   	
		case 'C': case 'c':
		  	 cis = 40;
		  	 break; 
#ifdef BOOTLOADER
		case 'B': case 'b':
			 cis = 50;
			 break;
#endif//BOOTLOADER		   
        default:
          cis = 255;
          break;
        }
      break;
    case 1:                                                     // cis=2: "?" arrived: print help
      if (CMD == '\r')
      {
        printHelp();
        cis = 0;
        break;
	  }
	  else cis = 255;
    break;
    case 2:                                                     // cis=2: "I" arrived: print version info
      if (CMD == '\r')
      {
      	printAbout();
      	cis = 0;
      	break;
      }
	  else cis = 255;	
	break;
    case 3:                                                     // cis=2: "S" arrived: print current settings
      switch( CMD )
	  {
	  case '=': break;
      case '?': break;
      case '\r': 	
	   	printf("\r\nChannel : %bd", rf_ch);
       	printf("\r\nDatarate: %bd", rf_dr);
			switch(rf_dr)
			{	
				case 0: 
					if ( mode == 0 ) 
					{
						printf("(DR: 2.4kbps, DEV: +-36kHz, BBBW: 75.2kHz)");
					}
					else
					{
						printf("(DR: 9.6kbps, DEV: +-90kHz, BBBW:184.8kHz)");
					}
					break;
				case 1: 
					printf("(DR: 4.8kbps, DEV: +-45kHz, BBBW: 95.3kHz)");
					break;
				case 2: 
					printf("(DR: 9.6kbps, DEV: +-45kHz, BBBW: 99.6.8kHz)");
					break;
				case 3: 
					printf("(DR: 19.2kbps, DEV: +-9.6kHz, BBBW: 28.8kHz)");
					break;
				case 4: 
					printf("(DR: 38.4kbps, DEV: +-19.2kHz, BBBW: 57.6kHz)");
					break;
				case 5: 
					printf("(DR: 57.6kbps, DEV: +-28.8kHz, BBBW: 86.4kHz)");
					break;
				case 6: 
					printf("(DR: 115.2kbps, DEV: +-57.6kHz, BBBW: 172.8kHz)");
					break;
				default:
					break;
			}					
      	printf("\r\nRF power: %bd", rf_pwr);
       	printOK();
       	cis = 0;
       	break;
      default:
	    cis = 255;
	    break;
	  }
    break;  
	case 10:                                                    // cis=3: "F" arrived: frequency setting
      switch (CMD)
        {
        case '=': break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          iparam = iparam * 10 + CMD - '0';
          break;
        case '\r':
		  if( iparam >= FreqSettings[0][rf_dr] )
		  {
			iparam = 0;
		  }
		   rf_ch = iparam;
	      set_frq(rf_ch);
         printOK();
          cis = 0;
	      break;
		default:
          cis = 255;
          break;
          }
	break;
    case 20:                                                    // cis=3: "D" arrived: datarate setting
      switch (CMD)
        {
        case '=': break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          iparam = iparam * 10 + CMD - '0';
          
		  break;
        case '\r':
		  if((mode == 0) && (iparam > 6))
		  {
		  	iparam = 0;
		  }
		  if((mode == 1) && (iparam > 1 ))
		  {
		  	iparam = 0;
		  }		 
		  		 
          rf_dr = iparam; 
		  set_dr(rf_dr);
		  printOK();
          cis = 0;
          break;
        default:
          cis = 255;
          break;
        }

      break;
    case 30:                                                    // cis=3: "P" arrived: output power setting
      switch (CMD)
      {
			case '=': break;
        	case '0': case '1': case '2': case '3': case '4':
        	case '5': case '6': case '7': case '8': case '9':
        		iparam = iparam * 10 + CMD - '0';
         	break;
        	case '\r':
			 	if (iparam > 7)
			 	{
					iparam = 0;	
			 	}
			 	rf_pwr = iparam;	
	       	set_pwr(rf_pwr);
	       	printOK();
	       	cis = 0;
	       	break;
			default:
         	cis = 255;
         	break;
      }
      break;
	 case 40:
    	if (CMD == '\r')
		{
			RFCWTest();
		}
		cis = 0;
		break;
#ifdef BOOTLOADER
	 case 50:
		// read from invalid Flash address to cause reset & goto BL mode
      cis = *((U8 SEG_CODE *) 0xFFFD);    
      break;
#endif//BOOTLOADER
    case 255:                                                   // Bad command or parameter
      printf("\r\nERROR\r\n>\r\n");
      cis = 0;
      break;
    }
}
