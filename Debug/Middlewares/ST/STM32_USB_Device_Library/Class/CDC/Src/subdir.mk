################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F205xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f2xx" -I"../system/include/cmsis/device" -I"../Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


