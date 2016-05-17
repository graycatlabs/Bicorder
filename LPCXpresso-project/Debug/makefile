################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include eGFX/SRC/Fonts/subdir.mk
-include eGFX/SRC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: bicorder.axf

# Tool invocations
bicorder.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/Debug" -Xlinker -Map="bicorder.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "bicorder_Debug.ld" -o "bicorder.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) bicorder.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "bicorder.axf"; # arm-none-eabi-objcopy -v -O binary "bicorder.axf" "bicorder.bin" ; # checksum -p LPC824 -d "bicorder.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
