################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/board_sysinit.c 

C_DEPS += \
./src/board.d \
./src/board_sysinit.d 

OBJS += \
./src/board.o \
./src/board_sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -I"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\inc" -I"C:\Users\bruno\Documents\LPC11U14\nxp_lpcxpresso_11u14_board_lib\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/board.d ./src/board.o ./src/board_sysinit.d ./src/board_sysinit.o

.PHONY: clean-src

