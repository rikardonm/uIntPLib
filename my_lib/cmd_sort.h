/*
 * cmd_sort.h
 *
 *  Created on: Nov 28, 2013
 *      Author: rikardo
 */

#ifndef CMD_SORT_H_
#define CMD_SORT_H_

#include "depl_spc/includeAll_sw.h"
#include "depl_spc/cmd_list.h"

#define MAX_BUFFER_SIZE				30

typedef struct{
	uint8_t charIn;
	uint8_t cmdBuffer[MAX_BUFFER_SIZE];
	uint16_t charOut[MAX_BUFFER_SIZE];
	uint8_t charOutPtr;
} CommandInstance;



void CommandSort(uint8_t *cmdString);




#endif /* CMD_SORT_H_ */
