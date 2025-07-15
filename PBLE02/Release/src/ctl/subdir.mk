################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ctl/event.c \
../src/ctl/output.c \
../src/ctl/stateMachine.c \
../src/ctl/timer.c \
../src/ctl/var.c 

C_DEPS += \
./src/ctl/event.d \
./src/ctl/output.d \
./src/ctl/stateMachine.d \
./src/ctl/timer.d \
./src/ctl/var.d 

OBJS += \
./src/ctl/event.o \
./src/ctl/output.o \
./src/ctl/stateMachine.o \
./src/ctl/timer.o \
./src/ctl/var.o 


# Each subdirectory must supply rules for building sources it contributes
src/ctl/%.o: ../src/ctl/%.c src/ctl/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11UXX__ -D__REDLIB__ -I"C:\Users\bruno\Documents\LPC11U14\nxp_lpcxpresso_11u14_board_lib\inc" -I"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\inc" -Os -fno-common -g -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-ctl

clean-src-2f-ctl:
	-$(RM) ./src/ctl/event.d ./src/ctl/event.o ./src/ctl/output.d ./src/ctl/output.o ./src/ctl/stateMachine.d ./src/ctl/stateMachine.o ./src/ctl/timer.d ./src/ctl/timer.o ./src/ctl/var.d ./src/ctl/var.o

.PHONY: clean-src-2f-ctl

