/**
* \file includeAll.h
* \brief Standard file to be included by all libraries.
* 
* This file has all needed files to be included by all libraries.
* Including all files does slow down compilation, however, facilitates the porting process.
* 
*
*/

#ifndef INCLUDEALL_H_
#define INCLUDEALL_H_

//!< Standard C variable types
#include "stdint.h"
#include "stdbool.h"

//!< Microcontroller include files
#include "msp430.h"						//!< msp430g2 launchpad include, example.
#include "derivative.h"					//!< freescale freedom board include, example.
#include "inc/lm4f120h5qr.h"				//!< stellaris board include, example, uses stellarisWare.


//!< Microcontroller specific functions and masks, such as delays.
#include "chipSpecific.h"


#include "libraryCompatible.h"
#include "externalCons.h"




#endif // INCLUDEALL_H_