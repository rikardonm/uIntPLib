/*
 * myUart.h
 *
 *  Created on: Nov 25, 2013
 *      Author: rikardo
 */

#ifndef MYUART_H_
#define MYUART_H_

#include "depl_spc/includeAll_sw.h"
#include "depl_spc/includeAll_hw.h"


/*
 * UART operation mode masks
 */
#define UART_NORMAL_OP_MODE					0x0001
#define UART_DIRECT_TRANSFER_MODE			0x0002



#define UART_BUFFER_SIZE	30

typedef struct{
	uint8_t RxBuffer[UART_BUFFER_SIZE];
	uint8_t RxBufferPtr;
	uint8_t TxBuffer[UART_BUFFER_SIZE];
	uint8_t TxBufferPtr;
	uint16_t Mode;
	uint8_t TxLastSent[UART_BUFFER_SIZE];
	uint8_t TxLastSentPtr;
}UARTInstance;


#define myUARTPC							UART0_BASE

#define myUARTSend(instance, charToGo)		MAP_UARTCharPutNonBlocking(instance, charToGo)
#define myUARTDelay(delay)					SysDelay(delay)
#define myUARTPCSend(charToGo)				myUARTSend(myUARTPC, charToGo)



void myUARTSendString(uint32_t instance, uint8_t *string);




#endif /* MYUART_H_ */
