################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Src/drivers/usb_host/usbh_diskio.c 

OBJS += \
./FATFS/Src/drivers/usb_host/usbh_diskio.o 

C_DEPS += \
./FATFS/Src/drivers/usb_host/usbh_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Src/drivers/usb_host/%.o FATFS/Src/drivers/usb_host/%.su FATFS/Src/drivers/usb_host/%.cyclo: ../FATFS/Src/drivers/usb_host/%.c FATFS/Src/drivers/usb_host/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS/Src" -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-Src-2f-drivers-2f-usb_host

clean-FATFS-2f-Src-2f-drivers-2f-usb_host:
	-$(RM) ./FATFS/Src/drivers/usb_host/usbh_diskio.cyclo ./FATFS/Src/drivers/usb_host/usbh_diskio.d ./FATFS/Src/drivers/usb_host/usbh_diskio.o ./FATFS/Src/drivers/usb_host/usbh_diskio.su

.PHONY: clean-FATFS-2f-Src-2f-drivers-2f-usb_host

