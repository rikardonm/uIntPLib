/*
 * libraryCompatible.h
 *
 *  Created on: Feb 5, 2014
 *      Author: rikardo
 */

#ifndef LIBRARYCOMPATIBLE_H_
#define LIBRARYCOMPATIBLE_H_

#include "includeAll.h"


//direct setting, uses a pre-casted object
#define PinSet(port, pin)		(port##_PSOR = pin)									//!< register write or API function.
#define PinClear(port, pin)		(port##_PCOR = pin)									//!< register write or API function.
#define PinToogle(port, pin)	(port##_PTOR = pin)									//!< register write or API function, optional.

//casts the address to the structure referenced in the memory mapping file
#define PinAddrSet(port, pin)	(GPIO_PSOR_REG((GPIO_MemMapPtr)port) = pin)			//!< direct memory address write.
#define PinAddrClear(port, pin)	(GPIO_PCOR_REG((GPIO_MemMapPtr)port) = pin)			//!< direct memory address write.
#define PinAddrToogle(port, pin)	(xx)											//!< to be implemented, optional, based on toogle registers.

#define PROCESSOR_DELAY_FACTOR	2													//!< number of cycles per CPU delay loop.
#define SysDelay(time)			SysDelayFRDM(time)									//!< dedicated CPU loop delay.
#define SysDelayUs(time)		SysDelay((time*BUS_CLOCK)/PROCESSOR_DELAY_FACTOR)	//!< uS delay, implemented as CPU delay.
#define SysDelayMs(time)		SysDelayUs(time*1000)								//!< CPU delay, \TODO: change another method for multi-tasking.

typedef unsigned int mcuRegType;													//!< mask to specific MCU register size, 16 or 32 bits.



#endif /* LIBRARYCOMPATIBLE_H_ */
