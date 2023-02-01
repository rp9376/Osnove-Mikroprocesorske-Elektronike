################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/LED.c \
../System/SCI.c \
../System/buf.c \
../System/kbd.c \
../System/periodic_services.c \
../System/timing_utils.c 

C_DEPS += \
./System/LED.d \
./System/SCI.d \
./System/buf.d \
./System/kbd.d \
./System/periodic_services.d \
./System/timing_utils.d 

OBJS += \
./System/LED.o \
./System/SCI.o \
./System/buf.o \
./System/kbd.o \
./System/periodic_services.o \
./System/timing_utils.o 


# Each subdirectory must supply rules for building sources it contributes
System/%.o: ../System/%.c System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sonja/Desktop/RokMapa/OME/HomeWorkspace (Cube Projects)/Vaja9/System/Include" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System

clean-System:
	-$(RM) ./System/LED.d ./System/LED.o ./System/SCI.d ./System/SCI.o ./System/buf.d ./System/buf.o ./System/kbd.d ./System/kbd.o ./System/periodic_services.d ./System/periodic_services.o ./System/timing_utils.d ./System/timing_utils.o

.PHONY: clean-System

