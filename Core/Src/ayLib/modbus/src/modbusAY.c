/*******************************************************************************
*** created			:	4.11.2023											****
********************************************************************************
*** file           	: 	modbysAY.c											****
*** brief          	: 	modbysAY source program body						****
********************************************************************************
***	source file																****
*** abdullahYuksel 2023 													****
*** www.linkedin.com/in/abdullah-yüksel-ehm									****
*** https://github.com/abdullahyuksel										****
********************************************************************************
*******************************************************************************/
#include "modbusAY.h"


TickTime_t idleTime, errorTime, waitResponseTime;


extern RingBuffer_t 	usartCommReceiveBuff;
extern Uart_Comm_t 		uartComm;

char sonuc=0;
uint16_t saat_tarih[6];	//READ HOLDING REGISTER(0x03)
uint16_t degerler[19];	//READ HOLDING REGISTER(0x03)
uint16_t degerler2[15]; // READ DIGITAL INPUT(0x01)
/**
  * @brief modbus init function
  * @param modbus pointer
  * @retval void
  */
void ModbusInit(Modbus_t *modbus)
{
	modbus->mode								= RTU;
	modbus->state								= IDLE;
	modbus->errorCode							= NoError;
	modbus->txMessage.txIndex					= 0;
	modbus->txMessage.newSendMessageStatus		= false;
	modbus->rxMessage.newReceiveMessageStatus	= false;
}
/**
  * @brief modbus control function
  * @param modbus pointer
  * @retval void
  */
void ModbusMasterControl(Modbus_t *modbus)
{
	switch(modbus->state)
	{
		case IDLE:
			//idle state: ready to send messages
			if(modbus->txMessage.newSendMessageStatus && TickTimerCheckElapsedTime(&idleTime))
			{
				// ready a message for the transmit
				modbus->txMessage.newSendMessageStatus = false;
				modbus->state				= SendRequest;
				modbus->txMessage.txIndex	= 0;
				TickTimerStopTime(&idleTime);
			}
			break;
		case SendRequest:
			// send query request
			modbus->txMessage.txData[modbus->txMessage.txIndex++]	= modbus->txMessage.slaveAddress;
			modbus->txMessage.txData[modbus->txMessage.txIndex++]	= modbus->txMessage.functionCode;


			switch (modbus->txMessage.functionCode)
			{
				case ReadCoilStatus:

					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					break;

				case ReadHoldingRegisters:

					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					break;

				case ReadInputStatus:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					break;

				case ReadInputRegisters:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					break;

				case WriteForceSingleCoil:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.writeData[0]);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[0]);
					break;

				case WritePresetSingleRegister:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.writeData[0]);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[0]);
					break;

				case WriteForceMultipleCoils:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[0]);	//bayt sayısı
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.writeData[1]);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[1]);
					break;

				case WritePresetMultipleRegisters:
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.startAddress);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.numOfRegisters);
					modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[0]);	//bayt sayısı
					for(int d=1; d <= modbus->txMessage.numOfRegisters; d++)
					{
						modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.writeData[d]);
						modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.writeData[d]);
					}
					break;
				default:
					break;
			}

			modbus->txMessage.crc16 = 0xFF;
			modbus->txMessage.crc16 = CRC16Calculator(modbus->txMessage.txData, modbus->txMessage.txIndex);
			modbus->txMessage.txData[modbus->txMessage.txIndex++]	= LSB(modbus->txMessage.crc16);
			modbus->txMessage.txData[modbus->txMessage.txIndex++]	= MSB(modbus->txMessage.crc16);

			RingBufferClearData(&usartCommReceiveBuff);

			ModbusMasterWrite(&uartComm, modbus->txMessage.txData, modbus->txMessage.txIndex);

			TickTimerSetTime(&waitResponseTime, 3000);

			modbus->state = WaitingForReply;
			break;
		case WaitingForReply:
			// waiting answer
			//fonksiyon kodu geldikten sonra anlamlı veri gelecek. bu kısmı bekle. sonra işlemlere başla
			if(usartCommReceiveBuff.writePoint > 2)
				modbus->rxMessage.newReceiveMessageStatus = true;

			if(modbus->rxMessage.newReceiveMessageStatus)
			{
				modbus->rxMessage.slaveAddress = usartCommReceiveBuff.pBuffer[SLAVE_ADDRESS];

				if((modbus->rxMessage.slaveAddress == modbus->txMessage.slaveAddress)
					//&& (modbus->rxMessage.functionCode == modbus->txMessage.functionCode)
					)
				{
					modbus->state = ProcessingReply;
					modbus->rxMessage.newReceiveMessageStatus=false;
				}
				else
				{
					RingBufferClearData(&usartCommReceiveBuff);
				}
			}
			else
			{
				if(TickTimerCheckElapsedTime(&waitResponseTime))
				{
					modbus->errorCode	= TimeOutError;
					modbus->state		= ProcessingError;
				}
			}
			break;
		case ProcessingReply:
			// If the answer arrives correctly within the expected time, it will be processed.
			modbus->rxMessage.functionCode = usartCommReceiveBuff.pBuffer[FUNCTION_CODE];

			//8. bit hata bitidir. bu nedenle ilk 7 biti alıyoruz.0b01111111 = 0x7f
			//bu 7 bitte fonksiyon kodu yazar. bizim beklediğimiz fonksiyomkodu değilse uygun olmayan fonksiyon kodu olarak tanımla
			if((modbus->rxMessage.functionCode & 0x7F) != modbus->txMessage.functionCode)
			{
				modbus->errorCode 	= InvalidFunctionError;
				modbus->state		= ProcessingError;
			}
			//fonksiyon kodunun 7. bitini oku. hatanın ne olduğunu istisna bitinden oku.
			if(BIT_READ(modbus->rxMessage.functionCode, 7))
			{
				modbus->errorCode = usartCommReceiveBuff.pBuffer[EXCEPTION_CODE];
				modbus->state = ProcessingError;
			}
			//yeni bir mesaj gelmediği durumda yeni gelen mesajın uzunluğunu alacağız
			//mesajın uzunluğu = mesaj + slave adresi(1)+fonksiyon adı(2)+bayt sayısı(3)+crc LSB(4)+crc MSB(5)
			//yani 5 sayısı mesajın toplam uzunluğundaki sabit kimlik verileridir.
			if((modbus->rxMessage.messageLenght == 0) && (modbus->rxMessage.functionCode <= ReadInputRegisters))
			{
				modbus->rxMessage.messageLenght = usartCommReceiveBuff.pBuffer[LENGTH_CODE] + 5;
			}
			else if(modbus->rxMessage.functionCode >= WriteForceSingleCoil)
			{
				modbus->rxMessage.messageLenght = modbus->txMessage.txIndex;

				if((modbus->rxMessage.functionCode == WriteForceMultipleCoils) || (modbus->rxMessage.functionCode == WritePresetMultipleRegisters))
					modbus->rxMessage.messageLenght = 8;
			}
			//bundan sonra bütün datayı bekle
			//write point mesaj length e eşitse bütün data gelmiştir crc kontrolü yap.
			if(usartCommReceiveBuff.writePoint >= modbus->rxMessage.messageLenght
					&& modbus->rxMessage.messageLenght != 0)
			{
				modbus->rxMessage.crc16 = 0xFFFF;
				memcpy(modbus->rxMessage.rxData, usartCommReceiveBuff.pBuffer, modbus->rxMessage.messageLenght);
				modbus->rxMessage.rxIndex = usartCommReceiveBuff.writePoint;
				modbus->rxMessage.messageLenght = 0;
				//neden -2? crc alanını çıkarıp crc öncesindeki alanı hesaplamamız gerekiyor.
				modbus->rxMessage.crc16 = CRC16Calculator(modbus->rxMessage.rxData, (modbus->rxMessage.rxIndex - 2));

				if((LSB(modbus->rxMessage.crc16) != modbus->rxMessage.rxData[modbus->rxMessage.rxIndex - 2])
						|| (MSB(modbus->rxMessage.crc16)!= modbus->rxMessage.rxData[modbus->rxMessage.rxIndex - 1]))
				{
					modbus->errorCode = InvalidCRC;
					modbus->state = ProcessingError;
				}

				if(modbus->state != ProcessingError)
				{
					switch (modbus->rxMessage.functionCode)
					{
						case ReadCoilStatus:

							//degerler_READ DIGITAL INPUT(0x01)
							for(int i=0; i<8; i++)
							{
								degerler2[i] = (uint8_t)(modbus->rxMessage.rxData[3] >> i & 0x01);
							}
							for(int k=8; k<16; k++)
							{
								degerler2[k] = (uint8_t)(modbus->rxMessage.rxData[4] >> (k-8) & 0x01);
							}


							break;
						case ReadInputStatus:
							sonuc = BIT_READ(modbus->rxMessage.rxData[3], 0);

							break;
						case ReadInputRegisters:
							//degerler
							uint8_t dataLen = modbus->rxMessage.rxData[2] / 2;
							uint8_t index =3;
							for(int i=0; i<dataLen; i++)
							{
								degerler[i] = (modbus->rxMessage.rxData[index + i + 1])|(modbus->rxMessage.rxData[index + i] << 8);
								index++;
							}
							break;
						case ReadHoldingRegisters:

							//degerler
							uint8_t dataLen2 = modbus->rxMessage.rxData[2] / 2;
							uint8_t index2 =3;
							for(int i=0; i<dataLen2; i++)
							{
								degerler[i] = (modbus->rxMessage.rxData[index2 + i + 1])|(modbus->rxMessage.rxData[index2 + i] << 8);
								index2++;
							}

//							//degerler_READ HOLDING REGISTER(0x03)
//							uint8_t dataLen = modbus->rxMessage.rxData[2] / 2;
//							uint8_t index =3;
//							for(int i=0; i<dataLen; i++)
//							{
//								degerler[i] = (modbus->rxMessage.rxData[index + i + 1])|(modbus->rxMessage.rxData[index + i] << 8);
//								index++;
//							}


//							//saat_tarih_READ HOLDING REGISTER(0x03)
//							uint8_t dataLen = modbus->rxMessage.rxData[2] / 2;
//							uint8_t index =3;
//							for(int i=0; i<dataLen; i++)
//							{
//								saat_tarih[i] = (modbus->rxMessage.rxData[index + i + 1])|(modbus->rxMessage.rxData[index + i] << 8);
//								index++;
//							}


							break;
						case WriteForceSingleCoil:
							//gelen cevaba göre işlem yapıldımı yapılmadımı izle
							if(ModbusElementsEqual(modbus->txMessage.txData, modbus->rxMessage.rxData, modbus->txMessage.txIndex))
								sonuc=1;
							else
								sonuc=0;

							/*
							 0x0000 Hata Reset
							 0x0001 Role Led Test
							 */

							break;
						case WriteForceMultipleCoils:
							//gelen cevaba göre işlem yapıldımı yapılmadımı izle
							if(modbus->rxMessage.rxData[5] == modbus->txMessage.numOfRegisters)
								sonuc=1;
							else
								sonuc=0;

							break;
						case WritePresetSingleRegister:
							//gelen cevaba göre işlem yapıldımı yapılmadımı izle
							if(ModbusElementsEqual(modbus->txMessage.txData, modbus->rxMessage.rxData, modbus->txMessage.txIndex))
								sonuc=1;
							else
								sonuc=0;


							break;
						case WritePresetMultipleRegisters:
							//gelen cevaba göre işlem yapıldımı yapılmadımı izle
							if(modbus->rxMessage.rxData[5] == modbus->txMessage.numOfRegisters)
								sonuc=1;
							else
								sonuc=0;
							break;
					}
					modbus->state = IDLE;
				}
			}



			break;
		case ProcessingError:
			// error state process
			if(!errorTime.activated)
			{
				TickTimerSetTime(&errorTime, 1000);
			}
			else if(TickTimerCheckElapsedTime(&errorTime))
			{

			}
			break;
		default:
			break;
	}
}

/**
  * @brief modbus compare to arrays
  * @param tx pointer, rx pointer, , number Of Elemets
  * @retval bool
  */
bool ModbusElementsEqual(uint8_t *txArray, uint8_t *rxArray, uint8_t numberOfElements)
{
	for(int i=0; i < numberOfElements; i++)
	{
		if(txArray[i] != rxArray[i])
			return false;
	}
	return true;
}

/**
  * @brief modbus read coil function
  * @param modbus pointer, slaveID, startAddress, number Of Coils
  * @retval void
  */
void ModbusReadCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfCiols)
{
	modbus->txMessage.functionCode			= ReadCoilStatus;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfCiols;
	modbus->state							= IDLE;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus 	= true;
		TickTimerSetTime(&idleTime, 100);
	}
	modbus->txMessage.newSendMessageStatus	= true;
}

/**
  * @brief modbus read holding registers function
  * @param modbus pointer, slaveID, startAddress, number Of registers
  * @retval void
  */
void ModbusReadHoldingRegisters(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegisters)
{
	modbus->txMessage.functionCode			= ReadHoldingRegisters;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfRegisters;
	modbus->state							= IDLE;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus 	= true;
		TickTimerSetTime(&idleTime, 100);
	}
//	modbus->txMessage.newSendMessageStatus	= true;
}

/**
  * @brief modbus read input registers function
  * @param modbus pointer, slaveID, startAddress, number Of registers
  * @retval void
  */
void ModbusReadInputRegisters(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegisters)
{
	modbus->txMessage.functionCode			= ReadInputRegisters;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfRegisters;
	modbus->state							= IDLE;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus 	= true;
		TickTimerSetTime(&idleTime, 100);
	}
}

/**
  * @brief modbus read input function
  * @param modbus pointer, slaveID, startAddress, number Of Input
  * @retval void
  */
void ModbusReadInputStatus(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfInputs)
{
	modbus->txMessage.functionCode			= ReadInputRegisters;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfInputs;
	modbus->state							= IDLE;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus = true;
		TickTimerSetTime(&idleTime, 100);
	}
//	modbus->txMessage.newSendMessageStatus	= true;
}

/**
  * @brief modbus force coil function
  * @param modbus pointer, slaveID, numberOfCoil, status
  * @retval void
  */
void ModbusWriteForceSingleCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t numberOfCoil, ModbusCoilStatus_t status)
{
	modbus->txMessage.functionCode			= WriteForceSingleCoil;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= numberOfCoil;
	modbus->state							= IDLE;


	modbus->txMessage.writeData[0] 			= status;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus = true;
		TickTimerSetTime(&idleTime, 100);
	}
//	modbus->txMessage.newSendMessageStatus	= true;
}

/**
  * @brief modbus force multiple coils function
  * @param modbus pointer, slaveID, startAddress, numberOfCoils, status
  * @retval void
  */
void ModbusWriteForceMultipleCoil(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfCoils, uint16_t coilsStatus)
{
	modbus->txMessage.functionCode			= WriteForceMultipleCoils;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfCoils;
	modbus->state							= IDLE;

	modbus->txMessage.writeData[0] 			= (uint8_t)(ceil((double)numberOfCoils/8));
	modbus->txMessage.writeData[1] 			= coilsStatus;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus = true;
		TickTimerSetTime(&idleTime, 100);
	}
}

/**
  * @brief modbus preset single function
  * @param modbus pointer, slaveID, numberOfRegister, status
  * @retval void
  */
void ModbusWritePresetSingleRegister(Modbus_t *modbus, uint8_t slaveId, uint16_t numberOfRegister, uint16_t data)
{
	modbus->txMessage.functionCode			= WritePresetSingleRegister;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= numberOfRegister;
	modbus->state							= IDLE;

	modbus->txMessage.writeData[0] 			= data;

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus = true;
		TickTimerSetTime(&idleTime, 100);
	}
}

/**
  * @brief modbus preset multiple function
  * @param modbus pointer, slaveID, numberOfRegister, data pointer
  * @retval void
  */
void ModbusWritePresetMultipleRegister(Modbus_t *modbus, uint8_t slaveId, uint16_t startAddress, uint16_t numberOfRegister, uint16_t* data)
{
	modbus->txMessage.functionCode			= WritePresetMultipleRegisters;
	modbus->txMessage.slaveAddress			= slaveId;
	modbus->txMessage.startAddress			= startAddress;
	modbus->txMessage.numOfRegisters		= numberOfRegister;
	modbus->state							= IDLE;

	modbus->txMessage.writeData[0] 			= numberOfRegister*2;

	for(int i=0; i<numberOfRegister; i++)
	{
		modbus->txMessage.writeData[i+1] = data[i];
	}

	if(modbus->state == IDLE && (!modbus->txMessage.newSendMessageStatus))
	{
		modbus->txMessage.newSendMessageStatus = true;
		TickTimerSetTime(&idleTime, 100);
	}
}

/**
  * @brief modbus write uart function
  * @param buffer pointer, lenght
  * @retval uint8_t
  */
uint8_t ModbusMasterWrite(Uart_Comm_t *uart, uint8_t *buffer, uint16_t lenght)
{

//	UartX_WriteString(&uartComm, &buffer);


	while(lenght)
	{
		UartX_WriteSingleChar(&uartComm, *buffer);
		buffer++;
		lenght--;
	}

	UartX_WriteIntControl(&uartComm);


	return 1;
}
