#ifndef lcd_h
#define lcd_h


#include "depl_spc/includeAll_hw.h"
#include "depl_spc/includeAll_sw.h"



#define LCD_splashscreen_row1	PROJECT_NAME			//!< geneartion of project name in LCD
#define LCD_splashscreen_row2	("rnm sys undvpd")		//!< creator's watermark

#define LCD_splashscreen2_row1	__DATE__				//!< compile date, used as program version
#define LCD_splashscreen2_row2	__TIME__				//!< compile time, used as program version



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
void LCDInit(void);
void LCDSendCmd(uint8_t cmd);
void LCDSendChar(uint8_t txt);
void LCDSend(uint8_t send);
void LCDPosition(uint8_t row, uint8_t col);
void LCDPositionNoDelay(uint8_t row, uint8_t col);
void LCDSendString(uint8_t *string, uint8_t breakLine);
void LCDSendNumStrict(int64_t num, uint8_t length,\
		uint8_t isSigned, uint8_t showZeros);
void LCDSendNum(int64_t num, uint8_t length,\
		uint8_t isSigned, uint8_t showZeros);
void LCDSendNumArray(uint8_t *vector);
void LCDClear(void);
void LCDSendHex(uint8_t *array);

//limited by uint64 max counting
#define maxLengthOut	16
void numToArray(int32_t num, uint8_t *array,\
				uint8_t length, uint16_t base);

void LCDRegisterSpecial(uint8_t number,\
						uint8_t *character);
void LCDShift(uint8_t shift);
void LCDHome(void);


void arrayToNum(uint8_t *array, uint32_t *num, uint8_t base);


void LCDSendVU(uint32_t num, uint32_t base);

#endif
