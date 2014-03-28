#include "my_use.h"




/*
 * Shift Serial Send function
 */
void __inline ShiftSerialSend(uint32_t data_port, uint32_t data_pin, \
					uint32_t clk_port, uint32_t clk_pin, uint8_t text)
{

	PinAddrClear(clk_port, clk_pin);
	char i=8;
	while(i>0)
	{
		if((text&0x80)==0)
			PinAddrClear(data_port, data_pin);
		else
			PinAddrSet(data_port, data_pin);
		text <<= 1;
		i--;
		PinAddrSet(clk_port, clk_pin);
		SysDelay(2);
		PinAddrClear(clk_port, clk_pin);
		SysDelay(2);
	}

}





