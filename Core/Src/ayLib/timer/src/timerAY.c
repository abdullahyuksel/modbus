/*******************************************************************************
*** created			:	3.11.2023											****
********************************************************************************
*** file           	: 	timerAY.c											****
*** brief          	: 	timerAY source program body							****
********************************************************************************
***	source file																****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/
#include "timerAY.h"

uint32_t msTick;

/**
  * @brief tick timer interrupt function
  * @param void
  * @retval void
  */
void TickTimerInterrupt(void)
{
	msTick++;
}

/**
  * @brief ick timer initialize
  * @param time pointer, interval
  * @retval void
  */
void TickTimerInit(TickTime_t *time, uint32_t intervalMs)
{
	TickTimerSetTime(time, intervalMs);

}

/**
  * @brief tick timer set time
  * @param time pointer, interval
  * @retval void
  */
void TickTimerSetTime(TickTime_t *time, uint32_t intervalMs)
{
	time->activated = true;
	time->interval = intervalMs;
	time->startTick = msTick;
}

/**
  * @brief tick timer stop time
  * @param time pointer
  * @retval void
  */
void TickTimerStopTime(TickTime_t *time)
{
	time->activated = false;
}

/**
  * @brief tick timer check time
  * @param time pointer
  * @retval void
  */
bool TickTimerCheckElapsedTime(TickTime_t *time)
{
	uint32_t currentTick;
	if(time->activated)
	{
		currentTick = msTick;
		if(time->startTick <= currentTick)
		{
			if(currentTick - time->startTick >= time->interval)
			{
				time->activated = false;
				return true;
			}
		}
		else
		{
			if((0xFFFFFFFF - (time->startTick - currentTick)) >= time->interval)
			{
				time->activated = false;
				return true;
			}
		}
	}

	return false;
}
