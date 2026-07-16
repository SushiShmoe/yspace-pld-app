################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32u575citx.s 

OBJS += \
./Core/Startup/startup_stm32u575citx.o 

S_DEPS += \
./Core/Startup/startup_stm32u575citx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32u575citx.d ./Core/Startup/startup_stm32u575citx.o

.PHONY: clean-Core-2f-Startup

