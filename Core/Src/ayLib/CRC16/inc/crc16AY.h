/*******************************************************************************
*** created			:	2.11.2023											****
********************************************************************************
*** file           	: 	crc16AY.h											****
*** brief          	: 	crc16AY include program body						****
********************************************************************************
***	include file															****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/

#ifndef SRC_AYLIB_CRC16_INC_CRC16AY_H_
#define SRC_AYLIB_CRC16_INC_CRC16AY_H_

#include "stdint.h"
#include "stdbool.h"



/**
  * @brief crc16 calculator
  * @param buffer pointer, length
  * @retval crc value
  */
uint16_t CRC16Calculator(uint8_t *buffer, uint16_t length);

#endif /* SRC_AYLIB_CRC16_INC_CRC16AY_H_ */
