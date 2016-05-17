################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/aeabi_romdiv_patch.s 

C_SRCS += \
../src/MoonLander-i2c.c \
../src/bicorder-compass.c \
../src/bicorder-plotter.c \
../src/bicorder.c \
../src/cr_startup_lpc82x.c \
../src/crp.c \
../src/eGFX_Driver_C12832A_LPC824.c \
../src/hmc5883l.c \
../src/htu21d.c \
../src/mtb.c \
../src/sysinit.c 

OBJS += \
./src/MoonLander-i2c.o \
./src/aeabi_romdiv_patch.o \
./src/bicorder-compass.o \
./src/bicorder-plotter.o \
./src/bicorder.o \
./src/cr_startup_lpc82x.o \
./src/crp.o \
./src/eGFX_Driver_C12832A_LPC824.o \
./src/hmc5883l.o \
./src/htu21d.o \
./src/mtb.o \
./src/sysinit.o 

C_DEPS += \
./src/MoonLander-i2c.d \
./src/bicorder-compass.d \
./src/bicorder-plotter.d \
./src/bicorder.d \
./src/cr_startup_lpc82x.d \
./src/crp.d \
./src/eGFX_Driver_C12832A_LPC824.d \
./src/hmc5883l.d \
./src/htu21d.d \
./src/mtb.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I"/home/ahiam/Dropbox/eGFX/SRC" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__USE_LPCOPEN -DNO_BOARD_LIB -D__LPC82X__ -D__REDLIB__ -I"/storage_b/Dropbox/NXPWorkspace/lpc_chip_82x/inc" -I/usr/local/lpcxpresso_8.0.0_526/lpcxpresso/tools/redlib/include -I/usr/local/lpcxpresso_8.0.0_526/lpcxpresso/tools/features/include -g3 -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


