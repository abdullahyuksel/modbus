/*******************************************************************************
*** created			:	3.11.2023											****
********************************************************************************
*** file           	: 	uartAY.h											****
*** brief          	: 	uartAY include program body							****
********************************************************************************
***	include file															****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/

#ifndef SRC_AYLIB_UART_INC_UARTAY_H_
#define SRC_AYLIB_UART_INC_UARTAY_H_

#include <ringBufferAY.h>
#include "main.h"
#include "stdarg.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

/*External Uart defines*/
#define UART_TX_EMPTY		1<<7
#define UART_TX_INT			1<<7
#define UART_DATA_7_BIT		0x00FF

#define BUFF_SIZE 			1024

/*External HAL UART handle */
extern UART_HandleTypeDef 	huart2;
#define USART_EX 			&huart2

/*External uart structure*/
typedef struct
{
	UART_HandleTypeDef 	*huart;
	RingBuffer_t		*ringBufferReceive;
	RingBuffer_t		*ringBufferTransmit;

}Uart_Comm_t;

/**
  * @brief external uart initialize
  * @param uart pointer
  * @retval void
  */
void UartX_Init(Uart_Comm_t *uart);

/**
  * @brief external uart write char
  * @param uart pointer, character
  * @retval void
  */
void UartX_WriteSingleChar(Uart_Comm_t *uart, char character);

/**
  * @brief external uart write string
  * @param uart pointer, string pointer
  * @retval void
  */
void UartX_WriteString(Uart_Comm_t *uart, char *str);

/**
  * @brief external uart write interrupt control
  * @param uart pointer
  * @retval void
  */
void UartX_WriteIntControl(Uart_Comm_t *uart);

/**
  * @brief external uart communication initialize
  * @param void
  * @retval void
  */
void UartX_CommInit(void);

/**
  * @brief external uart print function
  * @param char
  * @retval int
  */
int UartX_Printf(const char *format, ...);

/**
  * @brief external uart callback function
  * @param void
  * @retval void
  */
void UartX_InterruptCallBacks(void);

#endif /* SRC_AYLIB_UART_INC_UARTAY_H_ */
