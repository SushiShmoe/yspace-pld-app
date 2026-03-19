################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/libcsp/src/interfaces/csp_if_can.c \
../Libraries/libcsp/src/interfaces/csp_if_can_pbuf.c \
../Libraries/libcsp/src/interfaces/csp_if_i2c.c \
../Libraries/libcsp/src/interfaces/csp_if_lo.c \
../Libraries/libcsp/src/interfaces/csp_if_usart.c 

OBJS += \
./Libraries/libcsp/src/interfaces/csp_if_can.o \
./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.o \
./Libraries/libcsp/src/interfaces/csp_if_i2c.o \
./Libraries/libcsp/src/interfaces/csp_if_lo.o \
./Libraries/libcsp/src/interfaces/csp_if_usart.o 

C_DEPS += \
./Libraries/libcsp/src/interfaces/csp_if_can.d \
./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.d \
./Libraries/libcsp/src/interfaces/csp_if_i2c.d \
./Libraries/libcsp/src/interfaces/csp_if_lo.d \
./Libraries/libcsp/src/interfaces/csp_if_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/libcsp/src/interfaces/%.o Libraries/libcsp/src/interfaces/%.su Libraries/libcsp/src/interfaces/%.cyclo: ../Libraries/libcsp/src/interfaces/%.c Libraries/libcsp/src/interfaces/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-libcsp-2f-src-2f-interfaces

clean-Libraries-2f-libcsp-2f-src-2f-interfaces:
	-$(RM) ./Libraries/libcsp/src/interfaces/csp_if_can.cyclo ./Libraries/libcsp/src/interfaces/csp_if_can.d ./Libraries/libcsp/src/interfaces/csp_if_can.o ./Libraries/libcsp/src/interfaces/csp_if_can.su ./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.cyclo ./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.d ./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.o ./Libraries/libcsp/src/interfaces/csp_if_can_pbuf.su ./Libraries/libcsp/src/interfaces/csp_if_i2c.cyclo ./Libraries/libcsp/src/interfaces/csp_if_i2c.d ./Libraries/libcsp/src/interfaces/csp_if_i2c.o ./Libraries/libcsp/src/interfaces/csp_if_i2c.su ./Libraries/libcsp/src/interfaces/csp_if_lo.cyclo ./Libraries/libcsp/src/interfaces/csp_if_lo.d ./Libraries/libcsp/src/interfaces/csp_if_lo.o ./Libraries/libcsp/src/interfaces/csp_if_lo.su ./Libraries/libcsp/src/interfaces/csp_if_usart.cyclo ./Libraries/libcsp/src/interfaces/csp_if_usart.d ./Libraries/libcsp/src/interfaces/csp_if_usart.o ./Libraries/libcsp/src/interfaces/csp_if_usart.su

.PHONY: clean-Libraries-2f-libcsp-2f-src-2f-interfaces

