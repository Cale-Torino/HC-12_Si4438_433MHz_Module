/*
** ============================================================================
**
** FILE
**  EZLink_modem_cmd.h
**
** DESCRIPTION
**  Header files for Ezlink modem usage
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



#ifndef EZLink_Modem_cmd_H
#define EZLink_Modem_cmd_H


#include "S8051.h"
							/* ======================================= *
			                 *  F U N C T I O N   P R O T O T Y P E S  *
			                 * ======================================= */

void CMD_init(void);
void printAbout(void);
void printOK(void);
void printHelp(void);
void CmdExec(uint8 CMD);



#endif
