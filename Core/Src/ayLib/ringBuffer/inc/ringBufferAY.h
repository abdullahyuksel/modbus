/*******************************************************************************
*** created			:	2.11.2023											****
********************************************************************************
*** file           	: 	ringBufferAY.h										****
*** brief          	: 	ringBufferAY include program body					****
********************************************************************************
***	include file															****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/

#ifndef SRC_AYLIB_RINGBUFFER_INC_RINGBUFFERAY_H_
#define SRC_AYLIB_RINGBUFFER_INC_RINGBUFFERAY_H_

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
/**
  * @brief RingBuffer structure
  */
typedef struct
{
	unsigned char 	*pBuffer;
	uint32_t 		writePoint;
	uint32_t 		readPoint;
	uint16_t 		length;
}RingBuffer_t;

/**
  * @brief RingBuffer Initialize
  * @param buffer pointer, buffer length
  * @retval None
  */
void RingBufferInit(RingBuffer_t *pRingBuffer, uint8_t *buffer, uint16_t length);
/**
  * @brief RingBuffer Empty Request
  * @param buffer pointer
  * @retval true or not
  */
bool RingBufferIsEmpty(RingBuffer_t *pRingBuffer);
/**
  * @brief RingBuffer Full Request
  * @param buffer pointer
  * @retval true or not
  */
bool RingBufferIsFull(RingBuffer_t *pRingBuffer);
/**
  * @brief RingBuffer Adding Data
  * @param buffer pointer, character
  * @retval true or not
  */
bool RingBufferPushData(RingBuffer_t *pRingBuffer, uint8_t character);
/**
  * @brief RingBuffer Pull Data
  * @param buffer pointer
  * @retval int data
  */
int RingBufferPullData(RingBuffer_t *pRingBuffer);
/**
  * @brief RingBuffer clear Data
  * @param buffer pointer
  * @retval void
  */
void RingBufferClearData(RingBuffer_t *pRingBuffer);

#endif /* SRC_AYLIB_RINGBUFFER_INC_RINGBUFFERAY_H_ */
