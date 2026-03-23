################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/drivers/sd/sd_diskio.c 

OBJS += \
./FATFS/drivers/sd/sd_diskio.o 

C_DEPS += \
./FATFS/drivers/sd/sd_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/drivers/sd/%.o FATFS/drivers/sd/%.su FATFS/drivers/sd/%.cyclo: ../FATFS/drivers/sd/%.c FATFS/drivers/sd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS" -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-drivers-2f-sd

clean-FATFS-2f-drivers-2f-sd:
	-$(RM) ./FATFS/drivers/sd/sd_diskio.cyclo ./FATFS/drivers/sd/sd_diskio.d ./FATFS/drivers/sd/sd_diskio.o ./FATFS/drivers/sd/sd_diskio.su

.PHONY: clean-FATFS-2f-drivers-2f-sd

