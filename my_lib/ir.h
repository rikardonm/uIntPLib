#ifndef ir_h
#define ir_h



//main file header
#include "depl_spc/includeAll_sw.h"
#include "depl_spc/includeAll_hw.h"

#include "stdint.h"
#include "stdbool.h"


/*
 * need to declare:
 *

#define IRTX_FREQ			38000
#define IRTX_PORT			GPIO_PORTB_BASE
#define IRTX_PIN			GPIO_PIN_1
#define IRRX_PORT			GPIO_PORTB_BASE
#define IRRX_PIN			GPIO_PIN_0
//larger compiled file
#define IR_BY_SOFTWARE_EN
#define IR_BY_UART_EN
#define IR_UART_BASE		UART1_BASE
#define IR_BY_TIMER_EN
#define IR_TIMER_BASE		TIMER3_BASE



 */



/*
 * InfraRed transceiver library
 * todo:	uart
 * 			timer
 * 			software
 *
 * -> uart peripheral support
 * 		initiated for stellaris/tivaC uCs, uart IR coding support
 * 	-> timer peripheral support
 * 		common to all uCs
 * 		carrier frequency generation
 * 	-> software support
 * 		support for full software control and emulation
 * 		delay by cpu time use
 *
 *
 * 	devBy: rnm (17/11/13)
 */


/*
 * Op. Param.
 */
#define IR_MAX_INSTANCES			4

/*
 * Op. Masks
 */
#define IR_BY_SOFTWARE				0x0001
#define IR_BY_UART					0x0002
#define IR_BY_TIMER					0x0004
#define IR_BY_EXTERNAL_TIEMR		0x0008

#define IR_NEC_PROTOCOL				0x0010
#define IR_NEC_EXTENDED				0x0020
#define IR_MY_PROTOCOL				0x0040
#define IR_RC5_PROTOCOL				0x0080

#define IR_REPEAT_COMMAND_ENABLE	0x0100
#define IR_REPEAT_COMMAND_DISABLE	0x0000

/*
 * Protocol Definitions
 */

#define NEC_PULSE_TIME				562

#define RC5_PULSE_TIME				889



typedef struct{
	uint16_t Mode;				//IR_BY_XX | IR_XX_PROTOCOL
	uint8_t CarrierFrequency;	//in kHZ
	uint16_t CarrierPeriod;		// in uS
	uint32_t TxPin;
	uint32_t TxPort;
	uint32_t RxPin;
	uint32_t RxPort;
	uint16_t ReceiveAddress;
	uint16_t ReceiveBuffer;
	uint16_t Pulses;
	uint8_t LastData;
}IRInstance;


#define IRPinSet(port, pin)		GPIOPinWrite(port, pin, pin)
#define IRPinClear(port, pin)	GPIOPinWrite(port, pin, 0)
#define IRDelayMs(delay)		SysDelayMs(delay)
#define IRDelayUs(delay)		SysDelayUs(delay)
#define IRDelay(delay)			SysDelay(delay)



void IRInit(IRInstance *instPtr);
void IRSend(IRInstance *instPtr, uint16_t address, uint16_t byte);
void IRByteBySoftware(IRInstance *instPtr, uint16_t address, uint16_t byte);
void IRRepeat(uint32_t port, uint32_t pin, uint8_t pulses, uint16_t delay);



#endif// if_h
