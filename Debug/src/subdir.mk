################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_1602.c \
../src/i2c_eeprom.c \
../src/parpadeo.c \
../src/pulsador_irq.c \
../src/rtc_interno.c \
../src/systick.c \
../src/teclado_matricial.c 

OBJS += \
./src/display_1602.o \
./src/i2c_eeprom.o \
./src/parpadeo.o \
./src/pulsador_irq.o \
./src/rtc_interno.o \
./src/systick.o \
./src/teclado_matricial.o 

C_DEPS += \
./src/display_1602.d \
./src/i2c_eeprom.d \
./src/parpadeo.d \
./src/pulsador_irq.d \
./src/rtc_interno.d \
./src/systick.d \
./src/teclado_matricial.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DPULSADOR_IRQ -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -I"C:\Datos\Otros\Repo\lib_lucas_board\inc" -I"C:\Datos\Otros\Repo\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Datos\Otros\Repo\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


