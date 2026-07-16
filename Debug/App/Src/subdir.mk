################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/app.c \
../App/Src/app_LTC2983.c \
../App/Src/app_csp.c \
../App/Src/app_freertos.c 

OBJS += \
./App/Src/app.o \
./App/Src/app_LTC2983.o \
./App/Src/app_csp.o \
./App/Src/app_freertos.o 

C_DEPS += \
./App/Src/app.d \
./App/Src/app_LTC2983.d \
./App/Src/app_csp.d \
./App/Src/app_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/app.cyclo ./App/Src/app.d ./App/Src/app.o ./App/Src/app.su ./App/Src/app_LTC2983.cyclo ./App/Src/app_LTC2983.d ./App/Src/app_LTC2983.o ./App/Src/app_LTC2983.su ./App/Src/app_csp.cyclo ./App/Src/app_csp.d ./App/Src/app_csp.o ./App/Src/app_csp.su ./App/Src/app_freertos.cyclo ./App/Src/app_freertos.d ./App/Src/app_freertos.o ./App/Src/app_freertos.su

.PHONY: clean-App-2f-Src

