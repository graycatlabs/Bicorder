################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_1BPP.c \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_4BPP.c \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_8BPP.c \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_1BPP.c \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_4BPP.c \
/home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_8BPP.c 

OBJS += \
./eGFX/SRC/Fonts/FONT_3_5_1BPP.o \
./eGFX/SRC/Fonts/FONT_3_5_4BPP.o \
./eGFX/SRC/Fonts/FONT_3_5_8BPP.o \
./eGFX/SRC/Fonts/FONT_5_7_1BPP.o \
./eGFX/SRC/Fonts/FONT_5_7_4BPP.o \
./eGFX/SRC/Fonts/FONT_5_7_8BPP.o 

C_DEPS += \
./eGFX/SRC/Fonts/FONT_3_5_1BPP.d \
./eGFX/SRC/Fonts/FONT_3_5_4BPP.d \
./eGFX/SRC/Fonts/FONT_3_5_8BPP.d \
./eGFX/SRC/Fonts/FONT_5_7_1BPP.d \
./eGFX/SRC/Fonts/FONT_5_7_4BPP.d \
./eGFX/SRC/Fonts/FONT_5_7_8BPP.d 


# Each subdirectory must supply rules for building sources it contributes
eGFX/SRC/Fonts/FONT_3_5_1BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_1BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/Fonts/FONT_3_5_4BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_4BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/Fonts/FONT_3_5_8BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_3_5_8BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/Fonts/FONT_5_7_1BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_1BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/Fonts/FONT_5_7_4BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_4BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

eGFX/SRC/Fonts/FONT_5_7_8BPP.o: /home/ahiam/Dropbox/eGFX/SRC/Fonts/FONT_5_7_8BPP.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


