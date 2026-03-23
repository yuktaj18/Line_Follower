################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Src/drivers/template/user_diskio.c 

OBJS += \
./FATFS/Src/drivers/template/user_diskio.o 

C_DEPS += \
./FATFS/Src/drivers/template/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Src/drivers/template/%.o FATFS/Src/drivers/template/%.su FATFS/Src/drivers/template/%.cyclo: ../FATFS/Src/drivers/template/%.c FATFS/Src/drivers/template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS/Src" -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-Src-2f-drivers-2f-template

clean-FATFS-2f-Src-2f-drivers-2f-template:
	-$(RM) ./FATFS/Src/drivers/template/user_diskio.cyclo ./FATFS/Src/drivers/template/user_diskio.d ./FATFS/Src/drivers/template/user_diskio.o ./FATFS/Src/drivers/template/user_diskio.su

.PHONY: clean-FATFS-2f-Src-2f-drivers-2f-template

