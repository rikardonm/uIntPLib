/*
 * myUart.c
 *
 *  Created on: Nov 25, 2013
 *      Author: rikardo
 */


#include "myUart.h"



/*
 * Sends a string, NULL terminator
 * returns none
 */
void myUARTSendString(uint32_t instance, uint8_t *string)
{
	while(*string)
	{
		myUARTSend(instance, *string);
		string++;
		myUARTDelay(1);
	}
}

