#include "ir.h"

#include "ir.h"






/*
 * Calls IR init
 * Modes: IR_BY_SOFTWARE
 * 		  IR_BY_UART
 * 		  IR_BY_TIMER
 */
void IRInit(IRInstance *instPtr)
{

	if((instPtr->Mode&IR_BY_SOFTWARE)!=0)
	{
		instPtr->CarrierPeriod = (uint16_t) 1000/instPtr->CarrierFrequency;
		#ifdef IR_BY_SOFTWARE_EN
		/*
		 * for software modulation, configure delay timing
		 */
		if((instPtr->Mode & (IR_NEC_PROTOCOL|IR_NEC_EXTENDED))!=0)
			instPtr->Pulses = (uint16_t) (NEC_PULSE_TIME*((uint16_t) instPtr->CarrierFrequency))/2000;
		if((instPtr->Mode&IR_RC5_PROTOCOL)!=0)
			instPtr->Pulses = (uint16_t) (RC5_PULSE_TIME*((uint16_t) instPtr->CarrierFrequency))/1000;
		#endif
	}


	if(instPtr->Mode == IR_BY_UART)
	{
		#ifdef IR_BY_UART_EN

		#endif
	}


	if(instPtr->Mode == IR_BY_TIMER)
	{
		#ifdef IR_BY_TIMER_EN

		#endif
	}


}



/*
 * Sends IR data according to instance
 */
void IRSend(IRInstance *instPtr, uint16_t address, uint16_t byte)
{
	uint32_t data;
	uint8_t tempAddress=0;
	uint8_t tempByte=0;

#ifdef IR_BY_SOFTWARE_EN
	uint16_t pulses;
	uint8_t roller;
	uint16_t delay = instPtr->CarrierPeriod/2;
#endif

	if((instPtr->Mode&IR_NEC_PROTOCOL)!=0)						//inversão do endereço e dados
	{
		tempAddress = ~address;
		address = ((address&0xFF))|((tempAddress&0xFF)<<8);
		tempByte = ~byte;
		byte = ((byte&0xFF))|((tempByte&0xFF)<<8);
	}
	if((instPtr->Mode&(IR_NEC_PROTOCOL|IR_NEC_EXTENDED))!=0)
			data = address|byte<<16;

#ifdef IR_BY_SOFTWARE_EN
	if((instPtr->Mode&IR_BY_SOFTWARE)!=0)
	{
		if((instPtr->Mode&(IR_NEC_EXTENDED|IR_NEC_PROTOCOL))!=0)		//padrão de envio
		{
			pulses = instPtr->Pulses*32;
			roller = 32;
			while(pulses>0)						//start signal send 9ms
			{
				IRPinSet(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				IRPinClear(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				pulses--;
			}
			IRDelayMs(4);					//protocol wait time
			IRDelayUs(500);
			while(roller>0)
			{
				pulses = instPtr->Pulses;
				while(pulses>0)					//carrier send
				{
					IRPinSet(instPtr->TxPort, instPtr->TxPin);
					IRDelayUs(delay);
					IRPinClear(instPtr->TxPort, instPtr->TxPin);
					IRDelayUs(delay);
					pulses--;
				}
				if((data&0x1)!=0)
					IRDelayUs(NEC_PULSE_TIME*2);
				IRDelayUs(NEC_PULSE_TIME);
				data >>= 1;
				roller --;
			}
			pulses = instPtr->Pulses;
			while(pulses>0)					//end signal send 562.5 us
			{
				IRPinSet(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				IRPinClear(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				pulses--;
			}
		}
		if((instPtr->Mode&IR_RC5_PROTOCOL)!=0)
		{
			//todo: to be implemented. sem saco anymore.
		}
	}
#endif
#ifdef IR_BY_UART_EN
	if((instPtr->Mode&IR_BY_UART)!=0)
	{

		//todo: make uart send buffer/command
	}
#endif
#ifdef IR_BY_TIMER_EN

#endif
}


#ifdef IR_BY_SOFTWARE
/*
 * sends a modulated bit
 */
void __inline IRByteBySoftware(IRInstance *instPtr, uint16_t address, uint16_t byte)
{
	uint8_t tempAddress=0;
	uint8_t tempByte=0;
	uint16_t pulses;
	uint32_t data;
	uint8_t roller;
	uint16_t delay = instPtr->CarrierPeriod/2;

	if((instPtr->Mode&IR_NEC_PROTOCOL)!=0)						//inversão do endereço e dados
	{
		tempAddress = ~address;
		address = ((address&0xFF))|((tempAddress&0xFF)<<8);
		tempByte = ~byte;
		byte = ((byte&0xFF))|((tempByte&0xFF)<<8);
	}
	if((instPtr->Mode&(IR_NEC_EXTENDED|IR_NEC_PROTOCOL))!=0)		//padrão de envio
	{
		data = address|byte<<16;
		pulses = instPtr->Pulses*32;
		roller = 32;
		while(pulses>0)						//start signal send 9ms
		{
			IRPinSet(instPtr->TxPort, instPtr->TxPin);
			IRDelayUs(delay);
			IRPinClear(instPtr->TxPort, instPtr->TxPin);
			IRDelayUs(delay);
			pulses--;
		}
		IRDelayMs(4);					//protocol wait time
		IRDelayUs(500);
		while(roller>0)
		{
			pulses = instPtr->Pulses;
			while(pulses>0)					//carrier send
			{
				IRPinSet(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				IRPinClear(instPtr->TxPort, instPtr->TxPin);
				IRDelayUs(delay);
				pulses--;
			}
			if((data&0x1)!=0)
				IRDelayUs(NEC_PULSE_TIME*2);
			IRDelayUs(NEC_PULSE_TIME);
			data >>= 1;
			roller --;
		}
		pulses = instPtr->Pulses;
		while(pulses>0)					//end signal send 562.5 us
		{
			IRPinSet(instPtr->TxPort, instPtr->TxPin);
			IRDelayUs(delay);
			IRPinClear(instPtr->TxPort, instPtr->TxPin);
			IRDelayUs(delay);
			pulses--;
		}
	}
	if((instPtr->Mode&IR_RC5_PROTOCOL)!=0)
	{
		//todo: to be implemented. sem saco anymore.
	}
}



void __inline IRRepeat(uint32_t port, uint32_t pin, uint8_t pulses, uint16_t delay)
{
	uint8_t tempPulses;
	//fixme: repeat codes should be sent at 108ms intervals
	tempPulses = pulses;
	pulses *= 16;
	delay /= 2;
	while(pulses>0)					//start signal send 9ms
	{
		IRPinSet(port, pin);
		IRDelayUs(delay);
		IRPinClear(port, pin);
		IRDelayUs(delay);
		pulses--;
	}
	IRDelayMs(2);
	IRDelayUs(250);
	pulses = tempPulses;
	while(pulses>0)					//end signal send 562.5 us
	{
		IRPinSet(port, pin);
		IRDelayUs(delay);
		IRPinClear(port, pin);
		IRDelayUs(delay);
		pulses--;
	}
}




#endif //ir_by_software












