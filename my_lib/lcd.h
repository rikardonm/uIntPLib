/**
 * \file lcd.h
 * \author rnm (rikardo.nm@hotmail.com)
 * \data Apr 10th 2014
 * \brief LCD SoftWare Driver Library
 */

/** \defgroup lcd_h
 * 
 * This file contains the functions to properly (hopefully) drive the LCD peripheral.
 * Current implementation uses a serial shift register to drive the LCD in 8 bit mode.
 * 
 * Further modifications to this library include:
 * + Parallel data transfer (make function to).
 * 
 * For the complete execution of the library, the following macros have to be created
 * specifically for this library:
 * + LCD_SPLASHSCREEN1 \n (1 or 0)
 * + LCD_SPLASHSCREEN2 \n (1 or 0)
 * + LCD_SPLASHSCREEN_CLEAR \n (1 or 0)
 * 
 * The library uses theses global value macros:
 * + PROJECT_NAME \n ("string_of_name_here")
 * 
 * The library uses these global function macros:
 * + SysDelayUs(time) \n
 *		CPU delay loop, usually.
 * + PinAddrSet(port, pin) \n
 *		Direct address write.
 * + PinAddrClear(port, pin) \n
 *		Direct address write.
 * + ShiftSerialSend(DTA_PORT, DTA_PIN, CLK_PORT, CLK_PIN, text) \n
 *		Used by LCD_DTA_Send(text) function, determines how data is transfered.
 * 
 * The following external connection macros have to be set:
 * + LCD_RS_PORT \n (register address)
 * + LCD_RS_PIN	 \n (bit position)
 * + LCD_EN_PORT \n (register address)
 * + LCD_EN_PORT \n(bit position)
 * + LCD_DTA_PORT \n (register address)
 * + LCD_DTA_PIN \n (bit position)
 * + LCD_CLK_PIN \n (bit position)
 */

/** \addtogroup lcd_h */
/* @{ */


#ifndef lcd_h
#define lcd_h


#include "includeAll.h"

/**
 * \name LCD_Splahscreen
 * LCD splashscreen text configuration.
 */
 /** @{ */
#define LCD_splashscreen_row1	__DATE__				//!< compile date, used as program version
#define LCD_splashscreen_row2	__TIME__				//!< compile time, used as program version

#define LCD_splashscreen2_row1	PROJECT_NAME			//!< geneartion of project name in LCD
#define LCD_splashscreen2_row2	("rnm sys undvpd")		//!< creator's watermark
/** @{ */



/*
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



/**
 * \name LCD_Function_Masks
 * Function masks used in the lib.
 */
 /** @{ */
#define LCDDelay(x)				SysDelayUs(x)							//!< delay loop mask.
#define LCDPinSet(x, y)			PinAddrSet(x, y)						//!< pin set function mask.
#define LCDPinClear(x, y)		PinAddrClear(x,y)						//!< pin clear function mask.
#define LCD_DTA_Send(text)		ShiftSerialSend(LCD_DTA_Port, LCD_DTA_Pin, LCD_CLK_Port, LCD_CLK_Pin, text)	//!< lcd send function mask.

#define LCD_RS_High				LCDPinSet(LCD_RS_Port, LCD_RS_Pin)		//!< RS pin set mask.
#define LCD_RS_Low				LCDPinClear(LCD_RS_Port, LCD_RS_Pin)	//!< RS pin clear mask.
#define LCD_EN_High				LCDPinSet(LCD_EN_Port, LCD_EN_Pin)		//!< EN pin set mask.
#define LCD_EN_Low				LCDPinClear(LCD_EN_Port, LCD_EN_Pin)	//!< EN pin clear mask.
/** @} */


/**
 * \name LCD_Option_Flags
 * LCD options flags.
 */
 /** @{ */
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
/** @} */


/**
 * \name LCD_Options_Select
 * Defitions of initial LCD options configuration.
 */
 /** @{ */
#define LCD_DISPLAY_CONFIG		(LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_BLINK_OFF)
#define LCD_DISPLAY_INCREMENT	(LCD_INCREMENT|LCD_INCREMENT_NO_SHIFT)
/** @} */

typedef struct
{
	uint8_t row;
	uint8_t col;
	uint8_t display;
	uint8_t shift;
	uint8_t cgramAdress;
	uint8_t	specialChar[8];		//defined by fonts
}LCDStatus;

//! \todo create masks for LCD commands.


// \todo: fix this shit. decide if is to be used with structs or no use at all.

extern LCDStatus	LCD0Status;			//!< LCD struct for current position



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
/**
* @}
*/