/*
** ============================================================================
**
** FILE
**  Si4432.h
**
** DESCRIPTION
**  Header files for Si4432 usage, contains RF specific definition and type declaration
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

#ifndef Si4432_H
#define Si4432_H

#include "S8051.h"



                /* ======================================= *
                 *    APPLICATION SPECIFIC DEFINITIONS     *
                 * ======================================= */

//packet settings 
#define MAX_PAYLOAD					(40)
#define PREAMBLE_LENGTH				(8)
#define PD_LENGTH						(4)		//in byte


                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */
//definitions for register usage
#define	REG_READ							(0x00)
#define	REG_WRITE						(0x80)

#define NMBR_OF_SAMPLE_SETTING1		(7)
#define NMBR_OF_SAMPLE_SETTING2		(1)
#define NMBR_OF_PARAMETER				(14)
                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */
//RF stack enumerations 
typedef enum _RF_ENUM
{
	RF_OK				=	0x00,			//function response parameters
	RF_ERROR_TIMING		=	0x01,
	RF_ERROR_PARAMETER	=	0x02,
	RF_PACKET_RECEIVED	= 	0x03,
	RF_NO_PACKET		=	0x04,
	RF_CRC_ERROR		=   0x05,
} RF_ENUM;




typedef enum _RF_SAMPLE_SETTINGS
{
	DR2400BPS_DEV36KHZ			= 0,	
	DR4800BPS_DEV45KHZ			= 1,	
	DR9600BPS_DEV45KHZ			= 2,	
	DR19200BPS_DEV9_6KHZ			= 3,	
	DR38400BPS_DEV19_2KHZ		= 4,	
	DR57600BPS_DEV28_8KHZ		= 5,	
	DR115200BPS_DEV57_6KHZ		= 6,	
	
} RF_SAMPLE_SETTINGS;


typedef enum _RF_REG_MAP					//revV2&B1
{
  DeviceType 								= 0x00,
  DeviceVersion								= 0x01,
  DeviceStatus 								= 0x02,
  InterruptStatus1 							= 0x03,
  InterruptStatus2 							= 0x04,
  InterruptEnable1 							= 0x05,          
  InterruptEnable2 							= 0x06,         
  OperatingFunctionControl1 				= 0x07,
  OperatingFunctionControl2 				= 0x08,
  CrystalOscillatorLoadCapacitance 			= 0x09,
  MicrocontrollerOutputClock 				= 0x0A,
  GPIO0Configuration 						= 0x0B,
  GPIO1Configuration 						= 0x0C,         
  GPIO2Configuration						= 0x0D,
  IOPortConfiguration						= 0x0E,
  ADCConfiguration							= 0x0F,
  ADCSensorAmplifierOffset					= 0x10,
  ADCValue									= 0x11,
  TemperatureSensorControl					= 0x12,
  TemperatureValueOffset					= 0x13,
  WakeUpTimerPeriod1 						= 0x14,          
  WakeUpTimerPeriod2 						= 0x15,         
  WakeUpTimerPeriod3 						= 0x16,         
  WakeUpTimerValue1							= 0x17,
  WakeUpTimerValue2							= 0x18,
  LowDutyCycleModeDuration 					= 0x19,       
  LowBatteryDetectorThreshold  				= 0x1A,
  BatteryVoltageLevel 						= 0x1B,                          
  IFFilterBandwidth  						= 0x1C,                           
  AFCLoopGearshiftOverride					= 0x1D,
  AFCTimingControl 							= 0x1E,                              
  ClockRecoveryGearshiftOverride 			= 0x1F,              
  ClockRecoveryOversamplingRatio 			= 0x20,              
  ClockRecoveryOffset2 						= 0x21,                       
  ClockRecoveryOffset1 						= 0x22,                       
  ClockRecoveryOffset0 						= 0x23,                     
  ClockRecoveryTimingLoopGain1 				= 0x24,              
  ClockRecoveryTimingLoopGain0 				= 0x25,             
  ReceivedSignalStrengthIndicator 			= 0x26,          
  RSSIThresholdForClearChannelIndicator 	= 0x27,   
  AntennaDiversityRegister1					= 0x28,
  AntennaDiversityRegister2					= 0x29,
  AFCLimiter									= 0x2A,
  DataAccessControl 						= 0x30,                          
  EZmacStatus 								= 0x31,                                  
  HeaderControl1 							= 0x32,                               
  HeaderControl2 							= 0x33,                              
  PreambleLength 							= 0x34,                               
  PreambleDetectionControl 					= 0x35,                    
  SyncWord3 								= 0x36,                                   
  SyncWord2 								= 0x37,                                   
  SyncWord1 								= 0x38,                               
  SyncWord0 								= 0x39,                                
  TransmitHeader3							= 0x3A,                       
  TransmitHeader2 							= 0x3B,                             
  TransmitHeader1 							= 0x3C,                              
  TransmitHeader0 							= 0x3D,                             
  TransmitPacketLength 						= 0x3E,                         
  CheckHeader3 								= 0x3F,                                
  CheckHeader2 								= 0x40,                              
  CheckHeader1 								= 0x41,                             
  CheckHeader0 								= 0x42,                            
  HeaderEnable3 							= 0x43,                               
  HeaderEnable2 							= 0x44,                                 
  HeaderEnable1 							= 0x45,                                
  HeaderEnable0 							= 0x46,                              
  ReceivedHeader3 							= 0x47,                          
  ReceivedHeader2 							= 0x48,                         
  ReceivedHeader1 							= 0x49,                           
  ReceivedHeader0 							= 0x4A,                             
  ReceivedPacketLength						= 0x4B,
  AnalogTestBus 							= 0x50,                              
  DigitalTestBus 							= 0x51,                          
  TXRampControl 							= 0x52,                             
  PLLTuneTime 								= 0x53,                            
  CalibrationControl 						= 0x55,                     
  ModemTest 								= 0x56,                               
  ChargepumpTest 							= 0x57,                    
  ChargepumpCurrentTrimming_Override 		= 0x58,         
  DividerCurrentTrimming				 	= 0x59,    
  VCOCurrentTrimming 						= 0x5A,                           
  VCOCalibration_Override 					= 0x5B,                    
  SynthesizerTest 							= 0x5C,                              
  BlockEnableOverride1 						= 0x5D,                        
  BlockEnableOverride2 						= 0x5E,                      
  BlockEnableOverride3 						= 0x5F,                       
  ChannelFilterCoefficientAddress 			= 0x60,             
  ChannelFilterCoefficientValue 			= 0x61,            
  CrystalOscillator_ControlTest 			= 0x62,               
  RCOscillatorCoarseCalibration_Override 	= 0x63,    
  RCOscillatorFineCalibration_Override 		= 0x64,      
  LDOControlOverride 						= 0x65,                          
  DeltasigmaADCTuning1			 			= 0x67,
  DeltasigmaADCTuning2			 			= 0x68,
  AGCOverride1					 			= 0x69,
  AGCOverride2 								= 0x6A,
  GFSKFIRFilterCoefficientAddress 			= 0x6B,            
  GFSKFIRFilterCoefficientValue 			= 0x6C,              
  TXPower 									= 0x6D,                                   
  TXDataRate1 								= 0x6E,                            
  TXDataRate0 								= 0x6F,                              
  ModulationModeControl1 					= 0x70,                   
  ModulationModeControl2 					= 0x71,                   
  FrequencyDeviation 						= 0x72,                            
  FrequencyOffset 							= 0x73,                            
  FrequencyChannelControl					= 0x74,
  FrequencyBandSelect 						= 0x75,                        
  NominalCarrierFrequency1	 				= 0x76,                    
  NominalCarrierFrequency0 					= 0x77,                    
  FrequencyHoppingChannelSelect 			= 0x79,               
  FrequencyHoppingStepSize 					= 0x7A,                     
  TXFIFOControl1 							= 0x7C,                        
  TXFIFOControl2 							= 0x7D,    
  RXFIFOControl 							= 0x7E,                               
  FIFOAccess								= 0x7F, 
} RF_REG_MAP;

                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */
RF_ENUM RfInitHw(void);
RF_ENUM RFSetRfParameters(RF_SAMPLE_SETTINGS setting);
RF_ENUM RFIdle(void);
RF_ENUM RFTransmit(uint8 * packet, uint8 length);
RF_ENUM RFReceive(void);
RF_ENUM RFPacketReceived(uint8 * packet, uint8 * length);
RF_ENUM RxFIFOReset(void);
RF_ENUM TxFIFOReset(void);
RF_ENUM set_dr(RF_SAMPLE_SETTINGS setting);
RF_ENUM set_pwr(uint8 pwr);
RF_ENUM set_frq(uint8 frq);

void RFCWTest(void);

#endif
