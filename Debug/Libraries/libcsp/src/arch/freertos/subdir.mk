################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/libcsp/src/arch/freertos/csp_clock.c \
../Libraries/libcsp/src/arch/freertos/csp_malloc.c \
../Libraries/libcsp/src/arch/freertos/csp_queue.c \
../Libraries/libcsp/src/arch/freertos/csp_semaphore.c \
../Libraries/libcsp/src/arch/freertos/csp_system.c \
../Libraries/libcsp/src/arch/freertos/csp_thread.c \
../Libraries/libcsp/src/arch/freertos/csp_time.c 

OBJS += \
./Libraries/libcsp/src/arch/freertos/csp_clock.o \
./Libraries/libcsp/src/arch/freertos/csp_malloc.o \
./Libraries/libcsp/src/arch/freertos/csp_queue.o \
./Libraries/libcsp/src/arch/freertos/csp_semaphore.o \
./Libraries/libcsp/src/arch/freertos/csp_system.o \
./Libraries/libcsp/src/arch/freertos/csp_thread.o \
./Libraries/libcsp/src/arch/freertos/csp_time.o 

C_DEPS += \
./Libraries/libcsp/src/arch/freertos/csp_clock.d \
./Libraries/libcsp/src/arch/freertos/csp_malloc.d \
./Libraries/libcsp/src/arch/freertos/csp_queue.d \
./Libraries/libcsp/src/arch/freertos/csp_semaphore.d \
./Libraries/libcsp/src/arch/freertos/csp_system.d \
./Libraries/libcsp/src/arch/freertos/csp_thread.d \
./Libraries/libcsp/src/arch/freertos/csp_time.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/libcsp/src/arch/freertos/%.o Libraries/libcsp/src/arch/freertos/%.su Libraries/libcsp/src/arch/freertos/%.cyclo: ../Libraries/libcsp/src/arch/freertos/%.c Libraries/libcsp/src/arch/freertos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-libcsp-2f-src-2f-arch-2f-freertos

clean-Libraries-2f-libcsp-2f-src-2f-arch-2f-freertos:
	-$(RM) ./Libraries/libcsp/src/arch/freertos/csp_clock.cyclo ./Libraries/libcsp/src/arch/freertos/csp_clock.d ./Libraries/libcsp/src/arch/freertos/csp_clock.o ./Libraries/libcsp/src/arch/freertos/csp_clock.su ./Libraries/libcsp/src/arch/freertos/csp_malloc.cyclo ./Libraries/libcsp/src/arch/freertos/csp_malloc.d ./Libraries/libcsp/src/arch/freertos/csp_malloc.o ./Libraries/libcsp/src/arch/freertos/csp_malloc.su ./Libraries/libcsp/src/arch/freertos/csp_queue.cyclo ./Libraries/libcsp/src/arch/freertos/csp_queue.d ./Libraries/libcsp/src/arch/freertos/csp_queue.o ./Libraries/libcsp/src/arch/freertos/csp_queue.su ./Libraries/libcsp/src/arch/freertos/csp_semaphore.cyclo ./Libraries/libcsp/src/arch/freertos/csp_semaphore.d ./Libraries/libcsp/src/arch/freertos/csp_semaphore.o ./Libraries/libcsp/src/arch/freertos/csp_semaphore.su ./Libraries/libcsp/src/arch/freertos/csp_system.cyclo ./Libraries/libcsp/src/arch/freertos/csp_system.d ./Libraries/libcsp/src/arch/freertos/csp_system.o ./Libraries/libcsp/src/arch/freertos/csp_system.su ./Libraries/libcsp/src/arch/freertos/csp_thread.cyclo ./Libraries/libcsp/src/arch/freertos/csp_thread.d ./Libraries/libcsp/src/arch/freertos/csp_thread.o ./Libraries/libcsp/src/arch/freertos/csp_thread.su ./Libraries/libcsp/src/arch/freertos/csp_time.cyclo ./Libraries/libcsp/src/arch/freertos/csp_time.d ./Libraries/libcsp/src/arch/freertos/csp_time.o ./Libraries/libcsp/src/arch/freertos/csp_time.su

.PHONY: clean-Libraries-2f-libcsp-2f-src-2f-arch-2f-freertos

