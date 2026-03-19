################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LTC2983/common/lpldgen/src/cJSON.c \
../LTC2983/common/lpldgen/src/payloads.c \
../LTC2983/common/lpldgen/src/payloads_pretty_print.c \
../LTC2983/common/lpldgen/src/pld_ltc.c 

OBJS += \
./LTC2983/common/lpldgen/src/cJSON.o \
./LTC2983/common/lpldgen/src/payloads.o \
./LTC2983/common/lpldgen/src/payloads_pretty_print.o \
./LTC2983/common/lpldgen/src/pld_ltc.o 

C_DEPS += \
./LTC2983/common/lpldgen/src/cJSON.d \
./LTC2983/common/lpldgen/src/payloads.d \
./LTC2983/common/lpldgen/src/payloads_pretty_print.d \
./LTC2983/common/lpldgen/src/pld_ltc.d 


# Each subdirectory must supply rules for building sources it contributes
LTC2983/common/lpldgen/src/%.o LTC2983/common/lpldgen/src/%.su LTC2983/common/lpldgen/src/%.cyclo: ../LTC2983/common/lpldgen/src/%.c LTC2983/common/lpldgen/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LTC2983-2f-common-2f-lpldgen-2f-src

clean-LTC2983-2f-common-2f-lpldgen-2f-src:
	-$(RM) ./LTC2983/common/lpldgen/src/cJSON.cyclo ./LTC2983/common/lpldgen/src/cJSON.d ./LTC2983/common/lpldgen/src/cJSON.o ./LTC2983/common/lpldgen/src/cJSON.su ./LTC2983/common/lpldgen/src/payloads.cyclo ./LTC2983/common/lpldgen/src/payloads.d ./LTC2983/common/lpldgen/src/payloads.o ./LTC2983/common/lpldgen/src/payloads.su ./LTC2983/common/lpldgen/src/payloads_pretty_print.cyclo ./LTC2983/common/lpldgen/src/payloads_pretty_print.d ./LTC2983/common/lpldgen/src/payloads_pretty_print.o ./LTC2983/common/lpldgen/src/payloads_pretty_print.su ./LTC2983/common/lpldgen/src/pld_ltc.cyclo ./LTC2983/common/lpldgen/src/pld_ltc.d ./LTC2983/common/lpldgen/src/pld_ltc.o ./LTC2983/common/lpldgen/src/pld_ltc.su

.PHONY: clean-LTC2983-2f-common-2f-lpldgen-2f-src

