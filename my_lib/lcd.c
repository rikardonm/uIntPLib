
#include "lcd.h"




/**
 * Checks and defines boolean values.
 */
#ifndef true
#define true 1
#define false 0
#define trueDefinedLCD
#endif


/*
 * Initialization Sequence:
 * TODO: create masks for LCD commands
 */
#define lcd_vector_index	9
const char LCD_CmdInit_Vector [lcd_vector_index] = \
		{
			0x03, 0x38, 0x38, 0x38, 0x01, LCD_DISPLAY_CONFIG, LCD_DISPLAY_INCREMENT, 0x01, 0x02,
		};
/*
 * Delay time in uSs
 */
/**
 * LCD Init command delay vector, in uS
 */
const unsigned int LCD_InitDelay_Vector[lcd_vector_index] = \
		{
			8000, 800, 800, 800, 600, 600, 200, 200, 200
		};




/**
 *	\brief Initializes the LCD Module
 *	
 *	Called once at startup. Takes no parameters.
 *	
 *	\return None.
 */
void LCDInit(void)
{
	uint8_t Vector_Scan = 0;
	LCDDelay(15000);
	for(Vector_Scan=0; Vector_Scan < lcd_vector_index; Vector_Scan++)
	{
		LCDSendCmd(LCD_CmdInit_Vector[Vector_Scan]);
		LCDDelay(LCD_InitDelay_Vector[Vector_Scan]);
	}
	//splash screen
#if LCD_SPLASHSCREEN1 == 1
	LCDPosition(1,1);
	LCDSendString(LCD_splashscreen_row1, false);
	LCDPosition(2,1);
	LCDSendString(LCD_splashscreen_row2, false);
	LCDDelay(2*1000*1000);
#endif
#if LCD_SPLASHSCREEN2 == 1
	LCDPosition(1,1);
	LCDSendString(LCD_splashscreen2_row1, false);
	LCDPosition(2,1);
	LCDSendString(LCD_splashscreen2_row2, false);
	LCDDelay(2*1000*1000);
#endif
	LCDClear();
}

/*
 * Send a Command to the LCD
 */
void LCDSendCmd(uint8_t cmd)
{
	LCD_RS_Low;
	LCDSend(cmd);
}

/*
 * Send a Text to the LCD
 */
/**
 * \brief send single character to LCD.
 * 
 * \param txt char type data to be sent, 8 bits.
 */
void LCDSendChar(uint8_t txt)
{
	LCD_RS_High;
	LCDSend(txt);
	LCD0Status.col ++;
	LCD_RS_Low;
}

/*
 * Write on serial shifter, pulse LCD EN
 */
__inline void LCDSend(uint8_t send)
{
	LCD_EN_Low;
	LCD_DTA_Send(send);
	LCDDelay(4);
	LCD_EN_High;
	LCDDelay(4);
	LCD_EN_Low;
}

/*
 * Changes the LCD Cursor Position
 * Updates LCDStatus
 * PARAM: row, col
 */
void LCDPosition(uint8_t row, uint8_t col)
{
	LCD0Status.row = row;
	LCD0Status.col = col;
	col--;
	if(row==1)
		row = 0x80;
	if(row==2)
		row = 0xC0;
	LCDSendCmd(row+col);
	LCDDelay(20);
}

/*
 * Changes the LCD Cursor Position
 * Updates LCDStatus
 * PARAM: row, col
 */
void LCDPositionNoDelay(uint8_t row, uint8_t col)
{
	LCD0Status.row = row;
	LCD0Status.col = col;
	col--;
	if(row==1)
		row = 0x80;
	if(row==2)
		row = 0xC0;
	LCDSendCmd(row+col);
}


/*
 * Writes a string of characteres on display
 * Processes according to the ASCII code
 * 0 - NULL
 */
void LCDSendString(uint8_t *string, uint8_t breakLine)
{
	while(*string)
	{
		LCDSendChar(*string);
		string++;
		if(LCD0Status.col==LCD_col_num && breakLine==true)
			if(LCD0Status.row<=LCD_row_num)
				LCDPosition(LCD0Status.row+1, 1);
			else
				LCDPosition(0, 1);
	}
}




/*
 * TODO: make function to print string and remaining spaces in LCD
 */


/*
 * Prints a number, from a variable, to the LCD
 * PARAM: num, length, isSigned, showZeros
 * IF signed
 * 		Limits to a max of 10 digits to a positive number
 * 		Limits to a max of 9 digits to a negative number
 * ELSE
 * 		limits to 10 chars
 * IF showzeros
 * 		shows all leading zeros
 * else
 * 		supresses zeros; places space instead
 */
void LCDSendNumStrict(int64_t num, uint8_t length, uint8_t isSigned, uint8_t showZeros)
{
	uint8_t index =0;
	uint8_t out;
	uint64_t multiple = 1;
	limitCeilValue(length,10);
	if(num<0 && isSigned==true)
	{
		LCDSendChar('-');
		num *= -1;
		length--;
	}
	index = length;
	while(length>1)
	{
		multiple *= 10;
		length--;
	}
	while(index >= 1)
	{
		out = (uint32_t) (num/multiple);
		num -= out*(multiple);
		if(out!=0)
			showZeros = true;
		if(out==0 && showZeros==false)
			out -= 16;
		LCDSendChar(out+48);
		multiple /= 10;
		index--;
	}
}



/*
 * Prints a number, from a variable, to the LCD
 * PARAM: num, length, isSigned, showZeros
 * IF signed
 * 		Limits to a max of 10 digits to a positive number
 * 		Limits to a max of 9 digits to a negative number
 * ELSE
 * 		limits to 10 chars
 * IF showzeros
 * 		shows all leading zeros
 * else
 * 		supresses zeros; places space instead
 */
void LCDSendNum(int64_t num, uint8_t length, uint8_t isSigned, uint8_t showZeros)
{
	uint8_t index =0;
	uint8_t out = ' ';
	uint64_t multiple = 1;
	limitCeilValue(length,10);
	if(num<0 && isSigned==true)
	{
		out = '-';
		num *= -1;
	}
	LCDSendChar(out);
	index = length;
	while(length>1)
	{
		multiple *= 10;
		length--;
	}
	while(index >= 1)
	{
		out = (uint32_t) (num/multiple);
		num -= out*(multiple);
		if(out!=0)
			showZeros = true;
		if(out==0 && showZeros==false)
			out -= 16;
		LCDSendChar(out+48);
		multiple /= 10;
		index--;
	}
}


/*
 * Sends numerical values to LCD
 * Values between 0 and base;
 * max base value is defined as 32 (32bit wide buses)
 */
void LCDSendNumArray(uint8_t *index)
{
	while(*index<33)
	{
		LCDSendChar(*index+'0');
		index++;
	}
}

/*
 * Clears display
 * Updates LCDStatus
 */
void LCDClear(void)
{
	LCDSendCmd(0x01);
	LCD0Status.row=1;
	LCD0Status.col=1;
	LCDDelay(800);
}

/*
 * Turns
 * LCD_DISPLAY_ON/OFF
 * LCD_CURSOR_ON/OFF
 * LCD_BLINK_ON/OFF
 */
void LCDDisplayOn(uint8_t onOff)
{
	LCD0Status.display = onOff;
	LCDSendCmd(onOff);
}




/*
 * Prints the value of the array in hex format
 * As HEX, it'll print in base 16
 * Takes out 2 leading digits
 */
void LCDSendHex(uint8_t *array)
{
	uint8_t offset, temp;
	LCDSendChar('0');
	LCDSendChar('x');
	array += 2;
	while(*array<=32)
	{
		temp = *array;
		if(temp>9)
		{
			temp -= 10;
			offset = 'A';
		}
		else
			offset = '0';
		LCDSendChar(temp+offset);
		array++;
	}
}



//void LCDSendNum(long num, char length, uint8_t isSigned, uint8_t showZeros)

/*
 * Passes a number to a vector
 * num -> number
 * vector -> pointer to vector
 * base -> base of output (max: 32)
 *
 * Last number in vector output is 33
 */
void numToArray(int32_t num, uint8_t *array, uint8_t length, uint16_t base)
{
	uint16_t index =1;
	uint8_t out;
	uint64_t multiple = 1;

	limitCeilValue(length, (unsigned char) 1<<64/base);
	limitCeilValue(length, maxLengthOut);


	//create multiple number
	while(index<length)
	{
		multiple *= base;
		index++;
	}
	//sort multiples
	while(index >= 1)
	{
		//determines the multiple
		out = (uint8_t) (num/multiple);
		//takes out multiple
		num -= out*(multiple);

		//escreve no vetor, desloca indice
		*array = out;
		array++;
		multiple /= base;
		//change multiple position
		index--;
	}
	*array = 33;
}

/*
 * registers special characteres
 * number -> from 0 to 7
 * *character -> first index to 8 bytes long vector
 * 				scans char downward
 */
void LCDRegisterSpecial(uint8_t number, uint8_t *character)
{
	uint8_t scan=0, data=0;
	LCDSendCmd(0x40+(number<<3));
	do
	{
		data = *(character+scan);
		LCDDelay(640);
		LCDSendChar(data&0x1F);
		scan++;
	}
	while(scan<8);
	LCDDelay(320);
}

/*
 * Shifts data on LCD Display
 */
void LCDShift(uint8_t shift)
{
	LCDSendCmd(shift|LCD_SHIFT);
}

/*
 * Sends LCD cursor to home position
 * PARAM: none
 */
void LCDHome(void)
{
	LCDSendCmd(0x02);
	LCDDelay(1500);
}



void arrayToNum(uint8_t *array, uint32_t *num, uint8_t base)
{
	while(*array<33)
	{
		*num += *array * base;
		array++;
	}
}




void LCDSendVU(uint32_t num, uint32_t base)
{
	uint8_t index, pass=1;
	num	 = (unsigned int) num*(LCD_col_num*LCD_char_width)/base;
	while(num>0)
	{
		index = LCD_char_width;
		while(num<LCD_char_width)
		{
			index--;
			num++;
		}
		LCDSendChar(index);
		num -= LCD_char_width;
		pass++;
	}
	while(pass<=LCD_col_num)
	{
		pass++;
		LCDSendChar(0);
	}
}




#ifdef trueDefinedLCD
#undef true
#undef false
#endif



