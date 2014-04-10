/**
* \file externalCons.h
* \brief File containing external connections masks.
* 
* This file defines the external connections and definitions for the peripherals used in the current project.
*
*
*/

#ifndef external_cons_h
#define external_cons_h

#include "includeAll.h"

/**
* \brief LCD Connections
* Order of definitions complies with my_modules standard.
* Data Connection Pinout:
* -# GND
* -# DTA
* -# CLK
* -# EN
* -# RS
*/
#define LCD_DTA_Port	PTE_BASE_PTR				//!< LCD DTA Port.
#define LCD_DTA_Pin		IOPin_22					//!< LCD DTA Pin.

#define LCD_CLK_Port	PTE_BASE_PTR				//!< LCD CLK Port.
#define LCD_CLK_Pin		IOPin_23					//!< LCD CLK Pin.

#define LCD_RS_Port		PTE_BASE_PTR				//!< LCD RS Port.
#define LCD_RS_Pin		IOPin_30					//!< LCD RS Pin.

#define LCD_EN_Port		PTE_BASE_PTR				//!< LCD EN Port.
#define LCD_EN_Pin		IOPin_29					//!< LCD EN Pin.


#define LCD_row_num		2							//!< Number of rows in LCD.
#define LCD_col_num		16							//!< Number of columns in LCD.
#define LCD_char_heigh	8							//!< Height of LCD Character.
#define LCD_char_width	5							//!< Width of LCD Character.



#endif//external_cons_h
