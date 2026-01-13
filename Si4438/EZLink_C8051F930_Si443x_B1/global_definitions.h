/*
** ============================================================================
**
** FILE
**  global_definitions.h
**
** DESCRIPTION
**  Contains the global definitions
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

#define BOOTLOADER

//#define BAND_434
#define BAND_470
//#define BAND_868
//#define BAND_915
//#define BAND_950


//==============================================================
// RF specific definitions
//==============================================================
#ifdef  BAND_434
#ifdef BOOTLOADER
	#define FW_VERSION "01.4b"
#else
   #define FW_VERSION "01.4r"
#endif//BOOTLOADER
	#define HW_VERSION "01.0r"
   #define BAND "434" 
	//define the default radio frequency
   #define FREQ_BAND_SELECT 0x53							//frequency band select
   #define NOMINAL_CAR_FREQ1 0x53							//default carrier frequency
   #define NOMINAL_CAR_FREQ2 0x40
#endif

#ifdef  BAND_470
#ifdef BOOTLOADER
	#define FW_VERSION "01.4b"
#else
   #define FW_VERSION "01.4r"
#endif//BOOTLOADER
	#define HW_VERSION "01.0r"
   #define BAND "470" 
	//define the default radio frequency
   #define FREQ_BAND_SELECT 0x57							//frequency band select
   #define NOMINAL_CAR_FREQ1 0x19							//default carrier frequency
   #define NOMINAL_CAR_FREQ2 0x00
#endif

#ifdef  BAND_868
#ifdef BOOTLOADER
	#define FW_VERSION "01.4b"
#else
   #define FW_VERSION "01.4r"
#endif//BOOTLOADER
	#define HW_VERSION "01.0r"
	#define BAND "868"
   //define the default radio ferquency
   #define FREQ_BAND_SELECT 0x73							//frequency band select
   #define NOMINAL_CAR_FREQ1 0x2C							//default carrier frequency
   #define NOMINAL_CAR_FREQ2 0x60
#endif

#ifdef  BAND_915
#ifdef BOOTLOADER
	#define FW_VERSION "01.4b"
#else
   #define FW_VERSION "01.4r"
#endif//BOOTLOADER
	#define HW_VERSION "01.0r"
	#define BAND "915"
   //define the default radio ferquency
   #define FREQ_BAND_SELECT 0x75							//frequency band select
   #define NOMINAL_CAR_FREQ1 0x0A							//default carrier frequency
   #define NOMINAL_CAR_FREQ2 0x80
#endif



#ifdef  BAND_950
#ifdef BOOTLOADER
	#define FW_VERSION "01.4b"
#else
   #define FW_VERSION "01.4r"
#endif//BOOTLOADER
	#define HW_VERSION "01.0r"
	#define BAND "950"
   //define the default radio ferquency
   #define FREQ_BAND_SELECT 0x77							//frequency band select
   #define NOMINAL_CAR_FREQ1 0x8A							//default carrier frequency
   #define NOMINAL_CAR_FREQ2 0xC0
#endif
