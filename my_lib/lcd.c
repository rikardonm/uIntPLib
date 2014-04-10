/**
* \weakgroup lcd_h
* @{
*/
#include "lcd.h"


#ifndef true
#define true 1
#define false 0
#define trueDefinedLCD
#endif


#define lcd_vector_index	7			//!< Initialization command sequence length.

/**
 * Initialization Commands Sequence:
 */
const char LCD_CmdInit_Vector [lcd_vector_index] ={0x38, 0x38, 0x38, 0x01, LCD_DISPLAY_CONFIG, LCD_DISPLAY_INCREMENT, 0x01};

/**
 * LCD Init command delay vector, in uS.
 */
const unsigned int LCD_InitDelay_Vector[lcd_vector_index] ={8000, 200, 200, 16000, 600, 200, 15000};


/**
 *	\brief Initializes the LCD Module.
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
	LCDSendString(LCD_splashscreen_row1, 0);
	LCDPosition(2,1);
	LCDSendString(LCD_splashscreen_row2, 0);
	LCDDelay(2*1000*1000);
#endif
#if LCD_SPLASHSCREEN2 == 1
	LCDPosition(1,1);
	LCDSendString(LCD_splashscreen2_row1, false);
	LCDPosition(2,1);
	LCDSendString(LCD_splashscreen2_row2, false);
	LCDDelay(2*1000*1000);
#endif
#if LCD_SPLAHSCREEN_CLEAR == 1
	LCDClear();
#endif
}

/**
 * \brief Send a Command to the LCD.
 * \return None.
 */
void LCDSendCmd(uint8_t cmd)
{
	LCD_RS_Low;
	LCDSend(cmd);
}


/**
 * \brief send single character to LCD.
 * 
 * \param txt uint8_t type data to be sent, 8 bits.
 *
 * \return None.
 */
void LCDSendChar(uint8_t txt)
{
	LCD_RS_High;
	LCDSend(txt);
	LCD0Status.col ++;
	LCD_RS_Low;
}

/**
 * \brief Send data to LCD, no RS control.
 *
 * \param send uint8_t data to be sent.
 *
 * \return None.
 */
__inline void LCDSend(uint8_t send)
{
	LCD_EN_Low;
	LCD_DTA_Send(send);
	LCDDelay(4);
	LCD_EN_High;
	LCDDelay(4);
	LCD_EN_Low;
	//! \todo make function to send parallel data.
}

/**
 * \brief Set LCD write position
 *
 * \param row uint8_t row.
 * \param col uint8_t column.
 *
 * \return None.
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


/**
 * \brief Set LCD write position, no delay in function
 *
 * Sends the LCD position command but does not implement a delay after.
 * 
 * \param row uint8_t row.
 * \param col uint8_t column.
 *
 * \return None.
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


/**
 * \brief Send string to LCD
 * Writes a string of characteres on display
 * Processes according to the ASCII code
 * 0 - NULL
 *
 * \param *string uint8_t string to be sent.
 * \param breakLine uint8_t break line at the end of LCD length.
 *
 * \return None.
 */
void LCDSendString(uint8_t *string, uint8_t breakLine)
{
	while(*string)
	{
		LCDSendChar(*string);
		string++;
		if(LCD0Status.col==LCD_col_num && breakLine==true)
		{
			if(LCD0Status.row<=LCD_row_num)
				LCDPosition(LCD0Status.row+1, 1);
			else
				LCDPosition(0, 1);
		}
	}
}




/*
 * \todo make function to print string and remaining spaces in LCD
 */


/**
 * \brief Send decimal number to LCD with a strict length.
 * 
 * Writes a decimal number with a strict length in the LCD.
 * 
 * \param num int64_t number to be written.
 * \param length uint8_t length, in decimal digits, of the number.
 * \param isSigned uint8_t flag to determine if the number is to be treted as a negative number.
 * \param showZeros uint8_t flag to determine if leading zeros will be shown.
 *
 * \return None.
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



/**
 * \brief Send decimal number to LCD with a variable length.
 * 
 * Writes a decimal number with a variable length in the LCD.
 * 
 * \param num int64_t number to be written.
 * \param length uint8_t length, in decimal digits, of the number.
 * \param isSigned uint8_t flag to determine if the number is to be treted as a negative number.
 * \param showZeros uint8_t flag to determine if leading zeros will be shown.
 *
 * \return None.
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


/**
 * \brief Sends a number in a array to the LCD.
 *
 * Sends a number arranged in an array to the LCD. Each cell corresponds to a digit in the LCD.
 *
 * \param *index uint8_t base address of the array to be written.
 *
 * \return None.
 */
void LCDSendNumArray(uint8_t *index)
{
	while(*index<33)
	{
		LCDSendChar(*index+'0');
		index++;
	}
}

/**
 * \brief Clears the LCD.
 *
 * Sends a clear all command to the LCD.
 *
 * \return None.
 */
void LCDClear(void)
{
	LCDSendCmd(0x01);
	LCD0Status.row=1;
	LCD0Status.col=1;
	LCDDelay(800);
}


/**
 * \brief Configures LCD appearence option.
 *
 * Sends the logical combination of the following flags:
 * + LCD_DISPLAY_ON/OFF
 * + LCD_CURSOR_ON/OFF
 * + LCD_BLINK_ON/OFF
 * .
 * 
 * \return None.
 */
void LCDDisplayOn(uint8_t onOff)
{
	LCD0Status.display = onOff;
	LCDSendCmd(onOff);
}


/**
 * \brief Prints a decimal number in hexadecimal format.
 *
 * \param *array uint8_t number array to be written.
 *
 * \return None.
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


/**
 * \brief Converts a variable to an array of numbers.
 *
 * The termination of array is done by the number 33.
 * The highest selectable number base is 32.
 *
 * \param num int32_t number to be converted.
 * \param *array uint8_t destination array.
 * \param length uint8_t number length, in decimal digits.
 * \param base uint8_t base of output array.
 *
 * \return None.
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
/**
 * \brief Registers special characters in the LCD.
 * 
 * \param number uint8_t number, from 1 to 8, of special character to be transferred.
 * \param *character uint8_t array containing the bits of the character to be set.
 *
 * \return None.
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


/**
 * \brief Enables the data shift option in LCD.
 * 
 * Sets the configuration according to the following flags:
 * + LCD_SHIFT
 * + LCD_SHIFT_DISPLAY
 * + LCD_SHIFT_CURSOR
 * + LCD_SHIFT_RIGHT
 * + LCD_SHIFT_LEFT
 * .
 * 
 * \param shift uint8_t option flag to be set.
 *
 * \return None.
 */
void LCDShift(uint8_t shift)
{
	LCDSendCmd(shift|LCD_SHIFT);
}


/**
 * \brief Sends the LCD cursor to home position.
 *
 * \return None.
 */
void LCDHome(void)
{
	LCDSendCmd(0x02);
	LCDDelay(1500);
}


/**
 * \brief Converts a number array to a variable.
 * 
 * \param *array uint8_t source array.
 * \param *num uint32_t target variable.
 * \param base uint8_t base of digits in array.
 */
void arrayToNum(uint8_t *array, uint32_t *num, uint8_t base)
{
	while(*array<33)
	{
		*num += *array * base;
		array++;
	}
}



/**
 * \brief Send LCD VU level.
 *
 * This function uses special characters filled in horizontal increasing steps to make a Visual Units Display from the LCD.
 *
 * \param num uint32_t number to be written.
 * \param base uint32_t max number value.
 *
 * \return None.
 */
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


/**
 * @}
 */