/**
 * \brief LCD SW Driver Library
 *
 * This file contains the functions to properly (hopefully) drive the LCD peripheral.
 * Current implementation uses a serial shift register to drive the LCD in 8 bit mode.
 *
 * Further modifications to this library include:
 * + Parallel data transfer (make function to);
 * \data {__DATE__}
 *
 * For the complete execution of the library, the following macros have to be created
 * specifically for this library:
 * + LCD_SPLASHSCREEN1 	(1,0)
 * + LCD_SPLASHSCREEN2	(1,0)
 * + LCD_SPLASHSCREEN_CLEAR	(1,0)
 *
 * The library uses theses global value macros:
 * + PROJECT_NAME	("string_of_name_here")
 *
 * The library uses these global function macros:
 * + SysDelayUs(time)
 * + PinAddrSet(port, pin)
 * + PinAddrClear(port, pin)
 *
 * The following external connection macros have to be set:
 * + LCD_RS_PORT	(register address)
 * + LCD_RS_PIN		(bit position)
 * + LCD_EN_PORT	(register address)
 * + LCD_EN_PORT	(bit position)
 * + LCD_DTA_PORT	(register address)
 */

#ifndef lcd_h
#define lcd_h


#include "includeAll.h"

#define LCD_splashscreen_row1	__DATE__				//!< compile date, used as program version
#define LCD_splashscreen_row2	__TIME__				//!< compile time, used as program version

#define LCD_splashscreen2_row1	PROJECT_NAME			//!< geneartion of project name in LCD
#define LCD_splashscreen2_row2	("rnm sys undvpd")		//!< creator's watermark




/*
NEED TO DECLARE 

//LCD
#define LCD_RS			J1_05	//E5
#define LCD_RS_Port		GPIO_PORTE_BASE
#define LCD_RS_Pin		GPIO_PIN_5

#define LCD_EN			J1_06	//E4
#define LCD_EN_Port		GPIO_PORTE_BASE
#define LCD_EN_Pin		GPIO_PIN_4

#define LCD_DTA			J2_09	//A2
#define LCD_DTA_Port	GPIO_PORTA_BASE
#define LCD_DTA_Pin		GPIO_PIN_3

#define LCD_CLK			J2_10	//A3
#define LCD_CLK_Port	GPIO_PORTA_BASE
#define LCD_CLK_Pin		GPIO_PIN_2

#define LCD_row_num		2
#define LCD_col_num		16

LCDStatus LCD0Status;


#define LCD_splashscreen_row1	("odqd")
#define LCD_splashscreen_row2	("rnm sys undvpd")



uint8_t specialChar[8][8] = {	//ultima coluna, linha de baixo, reservada para cursor
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x07, 0x00, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x06, 0x01, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x05, 0x02, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x04, 0x03, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x00, 0x03, 0x04, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x02, 0x05, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x01, 0x06, 0x00,\
		0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x07, 0x00
		};



*/



/*
 * LIBRARY FOR LCD USE
 * SERIAL COMM
 * USE OF SHIFT REGISTERS FOR DATA
 */



//sub-function masks
//External Function Masks
#define LCDDelay(x)				SysDelayUs(x)
#define LCDPinSet(x, y)			PinAddrSet(x, y)
#define LCDPinClear(x, y)		PinAddrClear(x,y)



//sub-function masks
#define LCD_RS_High				LCDPinSet(LCD_RS_Port, LCD_RS_Pin)
#define LCD_RS_Low				LCDPinClear(LCD_RS_Port, LCD_RS_Pin)
#define LCD_EN_High				LCDPinSet(LCD_EN_Port, LCD_EN_Pin)
#define LCD_EN_Low				LCDPinClear(LCD_EN_Port, LCD_EN_Pin)
#define LCD_CLK_High			LCDPinSet(LCD_CLK_Port, LCD_CLK_Pin)
#define LCD_CLK_LoW				LCDPinClear(LCD_CLK_Port, LCD_CLK_Pin)
#define LCD_DTA_Send(text)		ShiftSerialSend(LCD_DTA_Port,\
								LCD_DTA_Pin,\
								LCD_CLK_Port,\
								LCD_CLK_Pin, text)


//LCD Command Masks
#define LCD_DISPLAY_ON			0x0C
#define LCD_DISPLAY_OFF			0x08
#define LCD_CURSOR_ON			0x0A
#define LCD_CURSOR_OFF			0x08
#define LCD_BLINK_ON			0x09
#define LCD_BLINK_OFF			0x08
#define LCD_SHIFT				0x10
#define LCD_SHIFT_DISPLAY		0x08
#define LCD_SHIFT_CURSOR		0x02
#define LCD_SHIFT_RIGHT			0x04
#define LCD_SHIFT_LEFT			0x00
#define LCD_SET_CGRAM			0x40
#define LCD_INCREMENT			0X04
#define LCD_INCREMENT_NO_SHIFT	0x00
#define	LCD_INCREMENT_SHIFT		0x01
#define LCD_INCREMENT_POSITIVE	0x02
#define LCD_INCREMENT_NEGATIVE	0x00


//LCD Command Initial State - Config
#define LCD_DISPLAY_CONFIG		(LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_BLINK_OFF)
#define LCD_DISPLAY_INCREMENT	(LCD_INCREMENT|LCD_INCREMENT_NO_SHIFT)


typedef struct
{
	uint8_t row;
	uint8_t col;
	uint8_t display;
	uint8_t shift;
	uint8_t cgramAdress;
	uint8_t	specialChar[8];		//defined by fonts
}LCDStatus;



// \TODO: fix this shit. decide if is to be used with structs or no use at all.
extern LCDStatus	LCD0Status;




//functions declarations
extern void LCDInit(void);
extern void LCDSendCmd(uint8_t cmd);
extern void LCDSendChar(uint8_t txt);
extern void LCDSend(uint8_t send);
extern void LCDPosition(uint8_t row, uint8_t col);
extern void LCDPositionNoDelay(uint8_t row, uint8_t col);
extern void LCDSendString(uint8_t *string, uint8_t breakLine);
extern void LCDSendNumStrict(int64_t num, uint8_t length,\
		uint8_t isSigned, uint8_t showZeros);
extern void LCDSendNum(int64_t num, uint8_t length,\
		uint8_t isSigned, uint8_t showZeros);
extern void LCDSendNumArray(uint8_t *vector);
extern void LCDClear(void);
extern void LCDSendHex(uint8_t *array);

//limited by uint64 max counting
#define maxLengthOut	16
extern void numToArray(int32_t num, uint8_t *array,\
				uint8_t length, uint16_t base);

extern void LCDRegisterSpecial(uint8_t number,\
						uint8_t *character);
extern void LCDShift(uint8_t shift);
extern void LCDHome(void);


extern void arrayToNum(uint8_t *array, uint32_t *num, uint8_t base);


extern void LCDSendVU(uint32_t num, uint32_t base);

#endif
