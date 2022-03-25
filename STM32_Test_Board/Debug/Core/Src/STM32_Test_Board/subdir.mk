################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/STM32_Test_Board/GPIO_Input.c \
../Core/Src/STM32_Test_Board/GPIO_Output.c \
../Core/Src/STM32_Test_Board/STM32_Test_Board.c 

OBJS += \
./Core/Src/STM32_Test_Board/GPIO_Input.o \
./Core/Src/STM32_Test_Board/GPIO_Output.o \
./Core/Src/STM32_Test_Board/STM32_Test_Board.o 

C_DEPS += \
./Core/Src/STM32_Test_Board/GPIO_Input.d \
./Core/Src/STM32_Test_Board/GPIO_Output.d \
./Core/Src/STM32_Test_Board/STM32_Test_Board.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/STM32_Test_Board/%.o Core/Src/STM32_Test_Board/%.su: ../Core/Src/STM32_Test_Board/%.c Core/Src/STM32_Test_Board/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-STM32_Test_Board

clean-Core-2f-Src-2f-STM32_Test_Board:
	-$(RM) ./Core/Src/STM32_Test_Board/GPIO_Input.d ./Core/Src/STM32_Test_Board/GPIO_Input.o ./Core/Src/STM32_Test_Board/GPIO_Input.su ./Core/Src/STM32_Test_Board/GPIO_Output.d ./Core/Src/STM32_Test_Board/GPIO_Output.o ./Core/Src/STM32_Test_Board/GPIO_Output.su ./Core/Src/STM32_Test_Board/STM32_Test_Board.d ./Core/Src/STM32_Test_Board/STM32_Test_Board.o ./Core/Src/STM32_Test_Board/STM32_Test_Board.su

.PHONY: clean-Core-2f-Src-2f-STM32_Test_Board

