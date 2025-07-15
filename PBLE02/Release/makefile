################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/hardware/subdir.mk
-include src/ctl/subdir.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := PBLE02
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: PBLE02.axf

# Tool invocations
PBLE02.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\bruno\Documents\LPC11U14\nxp_lpcxpresso_11u14_board_lib\Debug" -L"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\libs" -L"C:\Users\bruno\Documents\LPC11U14\lpc_chip_11uxx_lib\Debug" -Xlinker -Map="PBLE02.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "PBLE02_Release.ld" -o "PBLE02.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lusbd_11uxx_lib -lnxp_lpcxpresso_11u14_board_lib -llpc_chip_11uxx_lib
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) PBLE02.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "PBLE02.axf" ; arm-none-eabi-objcopy -v -O binary "PBLE02.axf" "PBLE02.bin" ; # checksum -p LPC11U14_201 -d "PBLE02.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
