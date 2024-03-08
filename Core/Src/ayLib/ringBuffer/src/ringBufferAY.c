/*******************************************************************************
*** created			:	2.11.2023											****
********************************************************************************
*** file           	: 	ringBufferAY.c										****
*** brief          	: 	ringBufferAY source program body					****
********************************************************************************
***	source file																****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/


#include <ringBufferAY.h>

/**
  * @brief RingBuffer Initialize
  * @param buffer pointer, buffer length
  * @retval None
  */
void RingBufferInit(RingBuffer_t *pRingBuffer, uint8_t *buffer, uint16_t length)
{
	pRingBuffer->writePoint = 0;
	pRingBuffer->readPoint	= 0;
	pRingBuffer->length		= length;
	pRingBuffer->pBuffer	= buffer;
}

/**
  * @brief RingBuffer Empty Request
  * @param buffer pointer
  * @retval true or not
  */
bool RingBufferIsEmpty(RingBuffer_t *pRingBuffer)
{
	//if write point and read point are at the same array point, buffer is empty
	return (pRingBuffer->readPoint == pRingBuffer->writePoint) ? true : false;
}

/**
  * @brief RingBuffer Full Request
  * @param buffer pointer
  * @retval true or not
  */
bool RingBufferIsFull(RingBuffer_t *pRingBuffer)
{
	// gap(write and read between) is calculating
	int nRead = pRingBuffer->writePoint - pRingBuffer->readPoint;
	//if notRead gap is negative, so it will be positive
	if (nRead < 0) nRead += pRingBuffer->length;
	//if buffer is full, return true value
	return (nRead == (pRingBuffer->length - 1)) ? true : false;
}

/**
  * @brief RingBuffer Adding Data
  * @param buffer pointer, character
  * @retval true or not
  */
bool RingBufferPushData(RingBuffer_t *pRingBuffer, uint8_t character)
{
	bool retVal = false;
	//if buffer is full, out of the add function
	if(!RingBufferIsFull(pRingBuffer))
	{
		//character will write for the last point
		pRingBuffer->pBuffer[pRingBuffer->writePoint] = character;
		//and write point will increasing
		pRingBuffer->writePoint++;
		//if it is at the last point, turn to first point
		if(pRingBuffer->writePoint == pRingBuffer->length)
			pRingBuffer->writePoint=0;
		//adding process is completed
		retVal = true;
	}

	return retVal;
}

/**
  * @brief RingBuffer Pull Data
  * @param buffer pointer
  * @retval int data
  */
int RingBufferPullData(RingBuffer_t *pRingBuffer)
{
	int character = -1;
	//if buffer is empty, out of the pull function
	if(!RingBufferIsEmpty(pRingBuffer))
	{
		//character will read for the last point
		 character = pRingBuffer->pBuffer[pRingBuffer->readPoint];
		//and read point will increasing
		pRingBuffer->readPoint++;
		//if it is at the last point, turn to first point
		if(pRingBuffer->readPoint == pRingBuffer->length)
			pRingBuffer->readPoint=0;

	}

	return character;
}

/**
  * @brief RingBuffer clear Data
  * @param buffer pointer
  * @retval void
  */
void RingBufferClearData(RingBuffer_t *pRingBuffer)
{
	pRingBuffer->writePoint = 0;
	pRingBuffer->readPoint 	= 0;
}
