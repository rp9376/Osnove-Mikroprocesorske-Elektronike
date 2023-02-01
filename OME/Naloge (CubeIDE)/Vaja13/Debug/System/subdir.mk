################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/LED.c \
../System/SCI.c \
../System/XPT2046_touch.c \
../System/buf.c \
../System/joystick.c \
../System/kbd.c \
../System/lcd.c \
../System/lcd_backlight.c \
../System/lcd_ili9341.c \
../System/periodic_services.c \
../System/timing_utils.c \
../System/ugui.c 

C_DEPS += \
./System/LED.d \
./System/SCI.d \
./System/XPT2046_touch.d \
./System/buf.d \
./System/joystick.d \
./System/kbd.d \
./System/lcd.d \
./System/lcd_backlight.d \
./System/lcd_ili9341.d \
./System/periodic_services.d \
./System/timing_utils.d \
./System/ugui.d 

OBJS += \
./System/LED.o \
./System/SCI.o \
./System/XPT2046_touch.o \
./System/buf.o \
./System/joystick.o \
./System/kbd.o \
./System/lcd.o \
./System/lcd_backlight.o \
./System/lcd_ili9341.o \
./System/periodic_services.o \
./System/timing_utils.o \
./System/ugui.o 


# Each subdirectory must supply rules for building sources it contributes
System/%.o System/%.su: ../System/%.c System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sonja/Desktop/RokMapa/OME/HomeWorkspace (Cube Projects)/Vaja13/System/Include" -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I"C:/Users/Sonja/Desktop/RokMapa/OME/HomeWorkspace (Cube Projects)/Vaja13/Application/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System

clean-System:
	-$(RM) ./System/LED.d ./System/LED.o ./System/LED.su ./System/SCI.d ./System/SCI.o ./System/SCI.su ./System/XPT2046_touch.d ./System/XPT2046_touch.o ./System/XPT2046_touch.su ./System/buf.d ./System/buf.o ./System/buf.su ./System/joystick.d ./System/joystick.o ./System/joystick.su ./System/kbd.d ./System/kbd.o ./System/kbd.su ./System/lcd.d ./System/lcd.o ./System/lcd.su ./System/lcd_backlight.d ./System/lcd_backlight.o ./System/lcd_backlight.su ./System/lcd_ili9341.d ./System/lcd_ili9341.o ./System/lcd_ili9341.su ./System/periodic_services.d ./System/periodic_services.o ./System/periodic_services.su ./System/timing_utils.d ./System/timing_utils.o ./System/timing_utils.su ./System/ugui.d ./System/ugui.o ./System/ugui.su

.PHONY: clean-System

