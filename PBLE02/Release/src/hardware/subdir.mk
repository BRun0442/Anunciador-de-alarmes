################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hardware/ADC.c \
../src/hardware/DAC.c \
../src/hardware/LCD.c \
../src/hardware/LED.c \
../src/hardware/Memoria.c \
../src/hardware/RTC.c \
../src/hardware/Serial.c \
../src/hardware/Teclado.c 

C_DEPS += \
./src/hardware/ADC.d \
./src/hardware/DAC.d \
./src/hardware/LCD.d \
./src/hardware/LED.d \
./src/hardware/Memoria.d \
./src/hardware/RTC.d \
./src/hardware/Serial.d \
./src/hardware/Teclado.d 

OBJS += \
./src/hardware/ADC.o \
./src/hardware/DAC.o \
./src/hardware/LCD.o \
./src/hardware/LED.o \
./src/hardware/Memoria.o \
./src/hardware/RTC.o \
./src/hardware/Serial.o \
./src/hardware/Teclado.o 


# Each subdirectory must supply rules for building sources it contributes
src/hardware/%.o: ../src/hardware/%.c src/hardware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -D__REDLIB__ -I"C:\Users\bruno\Documents\LPC11U14\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\inc" -Os -fno-common -g -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-hardware

clean-src-2f-hardware:
	-$(RM) ./src/hardware/ADC.d ./src/hardware/ADC.o ./src/hardware/DAC.d ./src/hardware/DAC.o ./src/hardware/LCD.d ./src/hardware/LCD.o ./src/hardware/LED.d ./src/hardware/LED.o ./src/hardware/Memoria.d ./src/hardware/Memoria.o ./src/hardware/RTC.d ./src/hardware/RTC.o ./src/hardware/Serial.d ./src/hardware/Serial.o ./src/hardware/Teclado.d ./src/hardware/Teclado.o

.PHONY: clean-src-2f-hardware

