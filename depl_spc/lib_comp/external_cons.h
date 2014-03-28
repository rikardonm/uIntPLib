#ifndef external_cons_h
#define external_cons_h


/*
 * file used to declare masks to external peripherals
 *
 */


/*
 * Definitions for LCD peripheral
 */
//LCD
#define LCD_RS_Port		PTE_BASE_PTR
#define LCD_RS_Pin		IOPin_30

#define LCD_EN_Port		PTE_BASE_PTR
#define LCD_EN_Pin		IOPin_29

#define LCD_DTA_Port		PTE_BASE_PTR
#define LCD_DTA_Pin		IOPin_22

#define LCD_CLK_Port		PTE_BASE_PTR
#define LCD_CLK_Pin		IOPin_23

#define LCD_row_num		2
#define LCD_col_num		16
#define LCD_char_heigh	8
#define LCD_char_width	5



#endif//external_cons_h
