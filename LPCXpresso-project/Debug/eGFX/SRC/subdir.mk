################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/ahiam/Dropbox/eGFX/SRC/eGFX.c \
/home/ahiam/Dropbox/eGFX/SRC/eGFX_BMP.c 

OBJS += \
./eGFX/SRC/eGFX.o \
./eGFX/SRC/eGFX_BMP.o 

C_DEPS += \
./eGFX/SRC/eGFX.d \
./eGFX/SRC/eGFX_BMP.d 


# Each subdirectory must supply rules for building sources it contributes
eGFX/SRC/eGFX.o: /home/ahiam/Dropbox/eGFX/SRC/eGFX.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/eGFX_BMP.o: /home/ahiam/Dropbox/eGFX/SRC/eGFX_BMP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


