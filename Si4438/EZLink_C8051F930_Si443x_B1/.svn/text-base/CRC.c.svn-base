//-----------------------------------------------------------------------------
// CRC.c
//-----------------------------------------------------------------------------
// Copyright (C) 2007 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This file contains the constant information for the Application Image
// CRC.  It should be included in the Application Image project.
//
// Target:         C8051F93x-C8051F92x
// Tool chain:     Generic
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (FB)
//    -4 MAR 2009
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <compiler_defs.h>             // compiler declarations
#include <C8051F930_defs.h>            // SFR declarations

// For initial download, uncomment '0xff' line, download to the target, and 
// use the "O" command to calculate the correct CRC.  Once known, comment out 
// the 0xFF line, and uncomment the following line, replacing the contents 
// with the value returned from the "O" command, but LSB-first.
// For example, if "O" returned 73f89dcd,
// the byte order would be { 0xcd, 0x9d, 0xf8, 0x73 }

SEGMENT_VARIABLE (CRC[4], U8, SEG_CODE) =
{ 0x0E, 0x35, 0xAA, 0xBE };
//{ 0xff, 0xff, 0xff, 0xff };
