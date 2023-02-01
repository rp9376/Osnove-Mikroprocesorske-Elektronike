################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/LED.c \
../System/buf.c \
../System/kbd.c 

C_DEPS += \
./System/LED.d \
./System/buf.d \
./System/kbd.d 

OBJS += \
./System/LED.o \
./System/buf.o \
./System/kbd.o 


# Each subdirectory must supply rules for building sources it contributes
System/%.o System/%.su: ../System/%.c System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sonja/Desktop/RokMapa/OME/HomeWorkspace (Cube Projects)/Vaja6/System/Include" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System

clean-System:
	-$(RM) ./System/LED.d ./System/LED.o ./System/LED.su ./System/buf.d ./System/buf.o ./System/buf.su ./System/kbd.d ./System/kbd.o ./System/kbd.su

.PHONY: clean-System

