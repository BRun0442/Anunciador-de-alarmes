################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/I2C.c \
../src/cr_startup_lpc11xx.c \
../src/programa.c \
../src/sysinit.c \
../src/util.c 

C_DEPS += \
./src/I2C.d \
./src/cr_startup_lpc11xx.d \
./src/programa.d \
./src/sysinit.d \
./src/util.d 

OBJS += \
./src/I2C.o \
./src/cr_startup_lpc11xx.o \
./src/programa.o \
./src/sysinit.o \
./src/util.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -D__REDLIB__ -I"C:\Users\bruno\Documents\LPC11U14\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\inc" -Os -fno-common -g -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/I2C.d ./src/I2C.o ./src/cr_startup_lpc11xx.d ./src/cr_startup_lpc11xx.o ./src/programa.d ./src/programa.o ./src/sysinit.d ./src/sysinit.o ./src/util.d ./src/util.o

.PHONY: clean-src

