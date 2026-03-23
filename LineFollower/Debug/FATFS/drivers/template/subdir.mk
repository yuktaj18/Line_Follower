################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/drivers/template/user_diskio.c 

OBJS += \
./FATFS/drivers/template/user_diskio.o 

C_DEPS += \
./FATFS/drivers/template/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/drivers/template/%.o FATFS/drivers/template/%.su FATFS/drivers/template/%.cyclo: ../FATFS/drivers/template/%.c FATFS/drivers/template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS" -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-drivers-2f-template

clean-FATFS-2f-drivers-2f-template:
	-$(RM) ./FATFS/drivers/template/user_diskio.cyclo ./FATFS/drivers/template/user_diskio.d ./FATFS/drivers/template/user_diskio.o ./FATFS/drivers/template/user_diskio.su

.PHONY: clean-FATFS-2f-drivers-2f-template

