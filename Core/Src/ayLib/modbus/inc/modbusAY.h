/*******************************************************************************
*** created			:	4.11.2023											****
********************************************************************************
*** file           	: 	modbysAY.h											****
*** brief          	: 	modbysAY include program body						****
********************************************************************************
***	include file															****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/

#ifndef SRC_AYLIB_MODBUS_INC_MODBUSAY_H_
#define SRC_AYLIB_MODBUS_INC_MODBUSAY_H_

#include "main.h"
#include "timerAY.h"
#include "crc16AY.h"
#include "uartAY.h"
#include "ringBufferAY.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

/*modbus data length defines*/
#define MODBUS_MAX_TX_SIZE	252
#define MODBUS_MAX_RX_SIZE	256

#define SLAVE_ADDRESS		0
#define FUNCTION_CODE		1
#define EXCEPTION_CODE		2
#define LENGTH_CODE			2

#define LSB(x)				(uint8_t)(x & 0xFF)
#define MSB(x)				(uint8_t)(x >> 8)
#define BIT_READ(x, y)			(uint8_t)(x >> y & 0x01)

/**
  * @brief modbus function enums
  */
typedef enum
{
	ReadCoilStatus					= 0x01,
	ReadInputStatus					= 0x02,
	ReadHoldingRegisters			= 0x03,
	ReadInputRegisters				= 0x04,
	WriteForceSingleCoil			= 0x05,
	WritePresetSingleRegister		= 0x06,
	WriteForceMultipleCoils			= 0x0F,
	WritePresetMultipleRegisters	= 0x10
}ModbusFunctionCode_t;

/**
  * @brief modbus mode enums
  */
typedef enum
{
	ASCII,
	RTU
}ModbusMode_t;

/**
  * @brief modbus coil status
  */
typedef enum
{
	Coil_Out_Status_Off		= 0x0000,
	Coil_Out_Status_On		= 0xFF00
}ModbusCoilStatus_t;

/**
  * @brief modbus state enums
  */
typedef enum
{
	IDLE,
	SendRequest,
	WaitingForReply,
	ProcessingReply,
	ProcessingError
}ModbusState_t;

/**
  * @brief modbus error enums
  */
typedef enum
{
	NoError					= 0,
	InvalidFunctionError	= 1,
	InvalidDataAddress		= 2,
	InvalidDataValue		= 3,
	SlaveDeviceError		= 4,
	InfoMessage				= 5,
	InvalidCRC				= 6,
	TimeOutError			= 7,
}ModbusErrorCode_t;

/**
  * @brief modbus tx frame structer
  */
typedef struct
{
	uint8_t 				slaveAddress;
	ModbusFunctionCode_t	functionCode;
	uint16_t				startAddress;
	uint16_t				numOfRegisters;
	uint16_t				writeData[MODBUS_MAX_TX_SIZE];
	uint8_t 				messageLenght;
	uint8_t					txData[MODBUS_MAX_TX_SIZE];
	uint8_t 				txIndex;
	uint16_t				crc16;
	bool 					newSendMessageStatus;
}ModbusTxMessage_t;

/**
  * @brief modbus rx frame structer
  */
typedef struct
{
	uint8_t 				messageLenght;
	uint8_t					rxData[MODBUS_MAX_RX_SIZE];
	uint8_t 				rxIndex;
	uint8_t					slaveAddress;
	ModbusFunctionCode_t	functionCode;
	TickTime_t				rxTime;
	uint16_t				crc16;
	bool 					newReceiveMessageStatus;
}ModbusRxMessage_t;

/**
  * @brief modbus control structer
  */
typedef struct
{
	ModbusRxMessage_t 		rxMessage;
	ModbusTxMessage_t		txMessage;
	ModbusMode_t			mode;
	ModbusState_t 			state;
	ModbusErrorCode_t		errorCode;
}Modbus_t;

/**
  * @brief modbus init function
  * @param modbus pointer
  * @retval void
  */
void ModbusInit(Modbus_t *modbus);
/**
  * @brief modbus control function
  * @param modbus pointer
  * @retval void
  */
void ModbusMasterControl(Modbus_t *modbus);

/**
  * @brief modbus read coil function
  * @param modbus pointer, slaveID, startAddress, number Of Coils
  * @retval void
  */
void ModbusReadCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfCiols);

/**
  * @brief modbus read holding registers function
  * @param modbus pointer, slaveID, startAddress, number Of registers
  * @retval void
  */
void ModbusReadHoldingRegisters(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegisters);

/**
  * @brief modbus read input function
  * @param modbus pointer, slaveID, startAddress, number Of Input
  * @retval void
  */
void ModbusReadInputStatus(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfInputs);

/**
  * @brief modbus read input registers function
  * @param modbus pointer, slaveID, startAddress, number Of registers
  * @retval void
  */
void ModbusReadInputRegisters(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegisters);

/**
  * @brief modbus force coil function
  * @param modbus pointer, slaveID, numberOfCoil, status
  * @retval void
  */
void ModbusWriteForceSingleCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t numberOfCoil, ModbusCoilStatus_t status);

/**
  * @brief modbus force multiple coils function
  * @param modbus pointer, slaveID, startAddress, numberOfCoils, coilsStatus
  * @retval void
  */
void ModbusWriteForceMultipleCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfCoils, uint16_t coilsStatus);

/**
  * @brief modbus preset single function
  * @param modbus pointer, slaveID, numberOfRegister, status
  * @retval void
  */
void ModbusWritePresetSingleRegister(Modbus_t *modbus, uint8_t slaveId, uint16_t numberOfRegister, uint16_t data);

/**
  * @brief modbus preset multiple function
  * @param modbus pointer, slaveID, numberOfRegister, data pointer
  * @retval void
  */
void ModbusWritePresetMultipleRegister(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegister, uint16_t* data);

/**
  * @brief modbus write uart function
  * @param buffer pointer, lenght
  * @retval uint8_t
  */
uint8_t ModbusMasterWrite(Uart_Comm_t *uart, uint8_t *buffer, uint16_t lenght);

/**
  * @brief modbus compare to arrays
  * @param tx pointer, rx pointer, , number Of Elemets
  * @retval bool
  */
bool ModbusElementsEqual(uint8_t *txArray, uint8_t *rxArray, uint8_t numberOfElements);
#endif /* SRC_AYLIB_MODBUS_INC_MODBUSAY_H_ */
