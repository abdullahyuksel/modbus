/*******************************************************************************
*** created			:	3.11.2023											****
********************************************************************************
*** file           	: 	timerAY.h											****
*** brief          	: 	timerAY include program body						****
********************************************************************************
***	include file															****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/

#ifndef SRC_AYLIB_TIMER_INC_TIMERAY_H_
#define SRC_AYLIB_TIMER_INC_TIMERAY_H_

#include "stdint.h"
#include "stdbool.h"

typedef struct
{
	uint32_t 	startTick;
	uint32_t 	interval;
	bool		activated;
}TickTime_t;

/**
  * @brief tick timer interrupt function
  * @param void
  * @retval void
  */
void TickTimerInterrupt(void);

/**
  * @brief tick timer initialize
  * @param time pointer, interval
  * @retval void
  */
void TickTimerInit(TickTime_t *time, uint32_t intervalMs);

/**
  * @brief tick timer set time
  * @param time pointer, interval
  * @retval void
  */
void TickTimerSetTime(TickTime_t *time, uint32_t intervalMs);

/**
  * @brief tick timer stop time
  * @param time pointer
  * @retval void
  */
void TickTimerStopTime(TickTime_t *time);

/**
  * @brief tick timer check time
  * @param time pointer
  * @retval void
  */
bool TickTimerCheckElapsedTime(TickTime_t *time);
#endif /* SRC_AYLIB_TIMER_INC_TIMERAY_H_ */
