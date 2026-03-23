################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Src/diskio.c \
../FATFS/Src/ff.c \
../FATFS/Src/ff_gen_drv.c \
../FATFS/Src/ffsystem_baremetal.c \
../FATFS/Src/ffsystem_cmsis_os.c \
../FATFS/Src/ffsystem_template.c \
../FATFS/Src/ffunicode.c 

OBJS += \
./FATFS/Src/diskio.o \
./FATFS/Src/ff.o \
./FATFS/Src/ff_gen_drv.o \
./FATFS/Src/ffsystem_baremetal.o \
./FATFS/Src/ffsystem_cmsis_os.o \
./FATFS/Src/ffsystem_template.o \
./FATFS/Src/ffunicode.o 

C_DEPS += \
./FATFS/Src/diskio.d \
./FATFS/Src/ff.d \
./FATFS/Src/ff_gen_drv.d \
./FATFS/Src/ffsystem_baremetal.d \
./FATFS/Src/ffsystem_cmsis_os.d \
./FATFS/Src/ffsystem_template.d \
./FATFS/Src/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Src/%.o FATFS/Src/%.su FATFS/Src/%.cyclo: ../FATFS/Src/%.c FATFS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/FATFS/Src" -I"C:/Users/yukta/STM32CubeIDE/workspace_1.19.0/stm32f1xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FATFS-2f-Src

clean-FATFS-2f-Src:
	-$(RM) ./FATFS/Src/diskio.cyclo ./FATFS/Src/diskio.d ./FATFS/Src/diskio.o ./FATFS/Src/diskio.su ./FATFS/Src/ff.cyclo ./FATFS/Src/ff.d ./FATFS/Src/ff.o ./FATFS/Src/ff.su ./FATFS/Src/ff_gen_drv.cyclo ./FATFS/Src/ff_gen_drv.d ./FATFS/Src/ff_gen_drv.o ./FATFS/Src/ff_gen_drv.su ./FATFS/Src/ffsystem_baremetal.cyclo ./FATFS/Src/ffsystem_baremetal.d ./FATFS/Src/ffsystem_baremetal.o ./FATFS/Src/ffsystem_baremetal.su ./FATFS/Src/ffsystem_cmsis_os.cyclo ./FATFS/Src/ffsystem_cmsis_os.d ./FATFS/Src/ffsystem_cmsis_os.o ./FATFS/Src/ffsystem_cmsis_os.su ./FATFS/Src/ffsystem_template.cyclo ./FATFS/Src/ffsystem_template.d ./FATFS/Src/ffsystem_template.o ./FATFS/Src/ffsystem_template.su ./FATFS/Src/ffunicode.cyclo ./FATFS/Src/ffunicode.d ./FATFS/Src/ffunicode.o ./FATFS/Src/ffunicode.su

.PHONY: clean-FATFS-2f-Src

