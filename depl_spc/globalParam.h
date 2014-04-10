/*
 * globalParam.h
 *
 *  Created on: Mar 26, 2014
 *      Author: rikardo
 */

#ifndef GLOBALPARAM_H_
#define GLOBALPARAM_H_


//<! LCD Peripheral Definitions
#define PROJECT_NAME        ("your projects name here")			//!< project name to be shown.
#define LCD_SPLASHSCREEN    	1  								//!< enables date and time of compilation.
#define LCD_SPLASHSCREEN1   	1  								//!< enables proejct name in 2 secs splash.
#define LCD_SPLASHSCREEN_CLEAR	0								//!< enables or disables LCDClear() after splashscreen timeout.


#define CPU_CLOCK	48											//!< CPU clock im MHz
#define BUS_CLOCK	CPU_CLOCK/2									//!< Bus clock in relation to CPU_CLOCK
#define CPUHZ_CLOCK	48000000									//!< CPU clock in Hz
#define BUSHZ_CLOCK	CPUHZ_CLOCK/2								//!< Bus clock in relation to CPUHZ_CLOCK



//!< GPIO Pin Masks
#define IOPin_0		0x00000001
#define IOPin_1		0x00000002
#define IOPin_2		0x00000004
#define IOPin_3		0x00000008
#define IOPin_4		0x00000010
#define IOPin_5		0x00000020
#define IOPin_6		0x00000040
#define IOPin_7		0x00000080
#define IOPin_8		0x00000100
#define IOPin_9		0x00000200
#define IOPin_10	0x00000400
#define IOPin_11	0x00000800
#define IOPin_12	0x00001000
#define IOPin_13	0x00002000
#define IOPin_14	0x00004000
#define IOPin_15	0x00008000
#define IOPin_16	0x00010000
#define IOPin_17	0x00020000
#define IOPin_18	0x00040000
#define IOPin_19	0x00080000
#define IOPin_20	0x00100000
#define IOPin_21	0x00200000
#define IOPin_22	0x00400000
#define IOPin_23	0x00800000
#define IOPin_24	0x01000000
#define IOPin_25	0x02000000
#define IOPin_26	0x04000000
#define IOPin_27	0x08000000
#define IOPin_28	0x10000000
#define IOPin_29	0x20000000
#define IOPin_30	0x40000000
#define IOPin_31	0x08000000



#endif /* GLOBALPARAM_H_ */
