/*******************************************************************************
*** created			:	3.11.2023											****
********************************************************************************
*** file           	: 	uartAY.c											****
*** brief          	: 	uartAY source program body							****
********************************************************************************
***	source file																****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/
#include "../inc/uartAY.h"

RingBuffer_t 	*usartReceiveBuff;
RingBuffer_t 	*usartTransmitBuff;

RingBuffer_t 	usartCommReceiveBuff;
uint8_t 		usartCommReceiveBuffer[BUFF_SIZE];
RingBuffer_t 	usartCommTransmitBuff;
uint8_t 		usartCommTransmitBuffer[BUFF_SIZE];

Uart_Comm_t 	uartComm;

char 			printBuffer[BUFF_SIZE];
va_list			arg;
/**
  * @brief external uart initialize
  * @param uart pointer
  * @retval void
  */
void UartX_Init(Uart_Comm_t *uart)
{
	//is usart defined as usart
	if(uart->huart == USART_EX)
	{
		//it is defining receiver  buffer
		usartReceiveBuff = uart->ringBufferReceive;
		//it is defining transmitter buffer
		usartTransmitBuff = uart->ringBufferTransmit;
	}
}

/**
  * @brief external uart write char
  * @param uart pointer, character
  * @retval void
  */
void UartX_WriteSingleChar(Uart_Comm_t *uart, char character)
{
	//it will write char at the transmitter buffer
	//but, firstly it is controlling. is transmitter buffer full
	if(RingBufferIsFull(uart->ringBufferTransmit))
	{
		//is there something transmitter interrupt process
		if(!(uart->huart->Instance->CR1 & UART_TX_INT))
		{
			//it will be transmit a char from transmitter buffer
			HAL_UART_Transmit_IT(USART_EX, (uint8_t*)RingBufferPullData(uart->ringBufferTransmit), 1);
		}
		while(RingBufferIsFull(uart->ringBufferTransmit));
	}
	//character will be added to transmit buffer
	RingBufferPushData(uart->ringBufferTransmit, character);
}

/**
  * @brief external uart write string
  * @param uart pointer, string pointer
  * @retval void
  */
void UartX_WriteString(Uart_Comm_t *uart, char *str)
{
	char *ptr;
	//str pointer characters will be defined to ptr pointer
	ptr = str;

	//until ptr is empty
	while(*ptr)
	{
		// will be sent one by one until ptr is empty
		UartX_WriteSingleChar(uart, *ptr);
		//ptr address will be increased
		ptr++;
	}
}

/**
  * @brief external uart write interrupt control
  * @param uart pointer
  * @retval void
  */
void UartX_WriteIntControl(Uart_Comm_t *uart)
{
	int check;

	//isn't transmitter interrupt active
	if(!(uart->huart->Instance->CR1 & UART_TX_INT))
	{
		//will be controlled transmitter buffer
		check = RingBufferPullData(uart->ringBufferTransmit);
		//is there data
		if(check > -1)
		{
			//will be transmit data
			uart->huart->Instance->DR = (uint8_t)(check & 0xFF);
			//will be active transmitter interrupt
			__HAL_UART_ENABLE_IT(uart->huart, UART_IT_TXE);
		}
	}
}

/**
  * @brief external uart communication initialize
  * @param void
  * @retval void
  */
void UartX_CommInit(void)
{
	//init ring buffers
	RingBufferInit(&usartCommReceiveBuff, usartCommReceiveBuffer, BUFF_SIZE);
	RingBufferInit(&usartCommTransmitBuff, usartCommTransmitBuffer, BUFF_SIZE);

	//define uart
	uartComm.huart = USART_EX;

	//start uart buffers
	uartComm.ringBufferReceive = &usartCommReceiveBuff;
	uartComm.ringBufferTransmit = &usartCommTransmitBuff;

	//start uart
	UartX_Init(&uartComm);

	//start uart receive interrupt
	__HAL_UART_ENABLE_IT(uartComm.huart, UART_IT_RXNE);
}

/**
  * @brief external uart print function
  * @param char
  * @retval int
  */
int UartX_Printf(const char *format, ...)
{
	int status;

	va_start(arg, format);
	status = vsnprintf(printBuffer, BUFF_SIZE, format, arg);
	va_end(arg);

	UartX_WriteString(&uartComm, printBuffer);
	UartX_WriteIntControl(&uartComm);
	return status;
}

/**
  * @brief external uart callback function
  * @param void
  * @retval void
  */
void UartX_InterruptCallBacks(void)
{
	char character;
	int check;

	// has data arrived?
	if(__HAL_UART_GET_FLAG(USART_EX, UART_FLAG_RXNE))
	{
		//get data from data register to the character
		character = (uint8_t)(uartComm.huart->Instance->DR & (uint8_t)UART_DATA_7_BIT);
		//character will be added to receive buffer
		if(RingBufferPushData(usartReceiveBuff, character) == false)
		{
			//if not write to receive buffer, empty it
			RingBufferPullData(usartReceiveBuff);
			//will write again character to receive buffer
			RingBufferPushData(usartReceiveBuff, character);
		}
		//clear receiver interrupt flag
		__HAL_UART_CLEAR_FLAG(USART_EX, UART_FLAG_RXNE);
	}

	//has data transmit
	if(__HAL_UART_GET_FLAG(USART_EX, UART_FLAG_TXE))
	{
		//will be controlled transmit buffer
		check = RingBufferPullData(usartTransmitBuff);

		//is there data
		if(check > -1)
		{
			//will be transmit data
			uartComm.huart->Instance->DR = check;
		}
		//if is transmit buffer empty, clear flags
		if(RingBufferIsEmpty(usartTransmitBuff))
		{
			//claering transmit complated flag
			__HAL_UART_CLEAR_FLAG(USART_EX, UART_FLAG_TC);
			//disabling transmit interrupt flag
			__HAL_UART_DISABLE_IT(USART_EX, UART_IT_TXE);
		}

	}
}

