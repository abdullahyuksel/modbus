################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ayLib/CRC16/src/crc16AY.c 

OBJS += \
./Core/Src/ayLib/CRC16/src/crc16AY.o 

C_DEPS += \
./Core/Src/ayLib/CRC16/src/crc16AY.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ayLib/CRC16/src/%.o Core/Src/ayLib/CRC16/src/%.su Core/Src/ayLib/CRC16/src/%.cyclo: ../Core/Src/ayLib/CRC16/src/%.c Core/Src/ayLib/CRC16/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/ringBuffer/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/timer/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/CRC16/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/modbus/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/uart/inc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ayLib-2f-CRC16-2f-src

clean-Core-2f-Src-2f-ayLib-2f-CRC16-2f-src:
	-$(RM) ./Core/Src/ayLib/CRC16/src/crc16AY.cyclo ./Core/Src/ayLib/CRC16/src/crc16AY.d ./Core/Src/ayLib/CRC16/src/crc16AY.o ./Core/Src/ayLib/CRC16/src/crc16AY.su

.PHONY: clean-Core-2f-Src-2f-ayLib-2f-CRC16-2f-src

