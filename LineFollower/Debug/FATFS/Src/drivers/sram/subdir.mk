################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Src/drivers/sram/sram_diskio.c 

OBJS += \
./FATFS/Src/drivers/sram/sram_diskio.o 

C_DEPS += \
./FATFS/Src/drivers/sram/sram_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Src/drivers/sram/%.o FATFS/Src/drivers/sram/%.su FATFS/Src/drivers/sram/%.cyclo: ../FATFS/Src/drivers/sram/%.c FATFS/Src/drivers/sram/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS/Src" -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-Src-2f-drivers-2f-sram

clean-FATFS-2f-Src-2f-drivers-2f-sram:
	-$(RM) ./FATFS/Src/drivers/sram/sram_diskio.cyclo ./FATFS/Src/drivers/sram/sram_diskio.d ./FATFS/Src/drivers/sram/sram_diskio.o ./FATFS/Src/drivers/sram/sram_diskio.su

.PHONY: clean-FATFS-2f-Src-2f-drivers-2f-sram

