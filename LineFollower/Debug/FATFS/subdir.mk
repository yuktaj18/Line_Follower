################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/diskio.c \
../FATFS/ff.c \
../FATFS/ff_gen_drv.c \
../FATFS/ffsystem_baremetal.c \
../FATFS/ffsystem_cmsis_os.c \
../FATFS/ffsystem_template.c \
../FATFS/ffunicode.c \
../FATFS/sd_diskio.c \
../FATFS/user_diskio.c 

OBJS += \
./FATFS/diskio.o \
./FATFS/ff.o \
./FATFS/ff_gen_drv.o \
./FATFS/ffsystem_baremetal.o \
./FATFS/ffsystem_cmsis_os.o \
./FATFS/ffsystem_template.o \
./FATFS/ffunicode.o \
./FATFS/sd_diskio.o \
./FATFS/user_diskio.o 

C_DEPS += \
./FATFS/diskio.d \
./FATFS/ff.d \
./FATFS/ff_gen_drv.d \
./FATFS/ffsystem_baremetal.d \
./FATFS/ffsystem_cmsis_os.d \
./FATFS/ffsystem_template.d \
./FATFS/ffunicode.d \
./FATFS/sd_diskio.d \
./FATFS/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/%.o FATFS/%.su FATFS/%.cyclo: ../FATFS/%.c FATFS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS" -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS

clean-FATFS:
	-$(RM) ./FATFS/diskio.cyclo ./FATFS/diskio.d ./FATFS/diskio.o ./FATFS/diskio.su ./FATFS/ff.cyclo ./FATFS/ff.d ./FATFS/ff.o ./FATFS/ff.su ./FATFS/ff_gen_drv.cyclo ./FATFS/ff_gen_drv.d ./FATFS/ff_gen_drv.o ./FATFS/ff_gen_drv.su ./FATFS/ffsystem_baremetal.cyclo ./FATFS/ffsystem_baremetal.d ./FATFS/ffsystem_baremetal.o ./FATFS/ffsystem_baremetal.su ./FATFS/ffsystem_cmsis_os.cyclo ./FATFS/ffsystem_cmsis_os.d ./FATFS/ffsystem_cmsis_os.o ./FATFS/ffsystem_cmsis_os.su ./FATFS/ffsystem_template.cyclo ./FATFS/ffsystem_template.d ./FATFS/ffsystem_template.o ./FATFS/ffsystem_template.su ./FATFS/ffunicode.cyclo ./FATFS/ffunicode.d ./FATFS/ffunicode.o ./FATFS/ffunicode.su ./FATFS/sd_diskio.cyclo ./FATFS/sd_diskio.d ./FATFS/sd_diskio.o ./FATFS/sd_diskio.su ./FATFS/user_diskio.cyclo ./FATFS/user_diskio.d ./FATFS/user_diskio.o ./FATFS/user_diskio.su

.PHONY: clean-FATFS

