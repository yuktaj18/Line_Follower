################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Src/drivers/sd/sd_diskio.c \
../FATFS/Src/drivers/sd/sd_diskio_dma_rtos.c \
../FATFS/Src/drivers/sd/sd_diskio_dma_standalone.c 

OBJS += \
./FATFS/Src/drivers/sd/sd_diskio.o \
./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.o \
./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.o 

C_DEPS += \
./FATFS/Src/drivers/sd/sd_diskio.d \
./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.d \
./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Src/drivers/sd/%.o FATFS/Src/drivers/sd/%.su FATFS/Src/drivers/sd/%.cyclo: ../FATFS/Src/drivers/sd/%.c FATFS/Src/drivers/sd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS/Src" -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-Src-2f-drivers-2f-sd

clean-FATFS-2f-Src-2f-drivers-2f-sd:
	-$(RM) ./FATFS/Src/drivers/sd/sd_diskio.cyclo ./FATFS/Src/drivers/sd/sd_diskio.d ./FATFS/Src/drivers/sd/sd_diskio.o ./FATFS/Src/drivers/sd/sd_diskio.su ./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.cyclo ./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.d ./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.o ./FATFS/Src/drivers/sd/sd_diskio_dma_rtos.su ./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.cyclo ./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.d ./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.o ./FATFS/Src/drivers/sd/sd_diskio_dma_standalone.su

.PHONY: clean-FATFS-2f-Src-2f-drivers-2f-sd

