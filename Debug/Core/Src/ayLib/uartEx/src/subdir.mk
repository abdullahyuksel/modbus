################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ayLib/uartEx/src/uartEx.c 

OBJS += \
./Core/Src/ayLib/uartEx/src/uartEx.o 

C_DEPS += \
./Core/Src/ayLib/uartEx/src/uartEx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ayLib/uartEx/src/%.o Core/Src/ayLib/uartEx/src/%.su Core/Src/ayLib/uartEx/src/%.cyclo: ../Core/Src/ayLib/uartEx/src/%.c Core/Src/ayLib/uartEx/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/gitHub/modbus/source/Core/Src/ayLib/uartEx/inc" -I"D:/gitHub/modbus/source/Core/Src/ayLib/ringBuffer/inc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ayLib-2f-uartEx-2f-src

clean-Core-2f-Src-2f-ayLib-2f-uartEx-2f-src:
	-$(RM) ./Core/Src/ayLib/uartEx/src/uartEx.cyclo ./Core/Src/ayLib/uartEx/src/uartEx.d ./Core/Src/ayLib/uartEx/src/uartEx.o ./Core/Src/ayLib/uartEx/src/uartEx.su

.PHONY: clean-Core-2f-Src-2f-ayLib-2f-uartEx-2f-src

