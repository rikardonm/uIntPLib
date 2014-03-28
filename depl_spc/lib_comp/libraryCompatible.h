/*
 * libraryCompatible.h
 *
 *  Created on: Feb 5, 2014
 *      Author: rikardo
 */

#ifndef LIBRARYCOMPATIBLE_H_
#define LIBRARYCOMPATIBLE_H_

#include "depl_spc/includeAll_hw.h"
#include "gpioPin_masks.h"


//direct setting, uses a pre-casted object
#define PinSet(port, pin)		(port##_PSOR = pin)
#define PinClear(port, pin)		(port##_PCOR = pin)
#define PinToogle(port, pin)	(port##_PTOR = pin)

//casts the address to the structure referenced in the memory mapping file
#define PinAddrSet(port, pin)	(GPIO_PSOR_REG((GPIO_MemMapPtr)port) = pin)
#define PinAddrClear(port, pin)	(GPIO_PCOR_REG((GPIO_MemMapPtr)port) = pin)



#define SysDelay(time)			SysDelayFRDM(time)			//chip specific
#define SysDelayUs(time)		SysDelay((time*BUS_CLOCK)/6)
#define SysDelayMs(time)		SysDelayUs(time*1000)





#endif /* LIBRARYCOMPATIBLE_H_ */
