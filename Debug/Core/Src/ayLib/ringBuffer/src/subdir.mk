################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ayLib/ringBuffer/src/ringBufferAY.c 

OBJS += \
./Core/Src/ayLib/ringBuffer/src/ringBufferAY.o 

C_DEPS += \
./Core/Src/ayLib/ringBuffer/src/ringBufferAY.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ayLib/ringBuffer/src/%.o Core/Src/ayLib/ringBuffer/src/%.su Core/Src/ayLib/ringBuffer/src/%.cyclo: ../Core/Src/ayLib/ringBuffer/src/%.c Core/Src/ayLib/ringBuffer/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/ringBuffer/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/timer/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/CRC16/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/modbus/inc" -I"C:/svn/jobs/projects/elzEnerji/redresor/sw/branches/modbus/source/Core/Src/ayLib/uart/inc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ayLib-2f-ringBuffer-2f-src

clean-Core-2f-Src-2f-ayLib-2f-ringBuffer-2f-src:
	-$(RM) ./Core/Src/ayLib/ringBuffer/src/ringBufferAY.cyclo ./Core/Src/ayLib/ringBuffer/src/ringBufferAY.d ./Core/Src/ayLib/ringBuffer/src/ringBufferAY.o ./Core/Src/ayLib/ringBuffer/src/ringBufferAY.su

.PHONY: clean-Core-2f-Src-2f-ayLib-2f-ringBuffer-2f-src

