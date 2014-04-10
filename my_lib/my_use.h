#ifndef my_use_h
#define my_use_h

#include "includeAll.h"


#define bTrue0				0x01
#define bTrue1				0x02
#define bTrue2				0x04
#define bTrue3				0x08
#define	bTrue4				0x10
#define	bTrue5				0x20
#define bTrue6				0x40
#define bTrue7				0x80

#define charDecadeLength	3
#define charBinaryLength	8

#define shortDecadeLength	5
#define shortBinaryLength	16

#define intDecadeLength		10
#define intBinaryLength		32



//function masks
#define	limitCeilValue(value, lim)					if(value>=lim)\
													value=lim;
#define limitCycleValueUpZero(value,lim)			if(value>=lim)\
													value=0;
#define limitCycleValueUpOff(value, lim, reset)		if(value>=lim)\
													value=reset;
#define limitFloorValue(value, lim)					if(value<=lim)\
													value=lim;




/*
 * Function Declarations
 */
void ShiftSerialSend(mcuRegType data_port, mcuRegType data_pin, \
		mcuRegType clk_port, mcuRegType clk_pin, uint8_t text);









#endif// my_use_h
