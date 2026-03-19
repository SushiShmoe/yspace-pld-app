################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/libcsp/src/csp_bridge.c \
../Libraries/libcsp/src/csp_buffer.c \
../Libraries/libcsp/src/csp_conn.c \
../Libraries/libcsp/src/csp_crc32.c \
../Libraries/libcsp/src/csp_debug.c \
../Libraries/libcsp/src/csp_dedup.c \
../Libraries/libcsp/src/csp_endian.c \
../Libraries/libcsp/src/csp_hex_dump.c \
../Libraries/libcsp/src/csp_iflist.c \
../Libraries/libcsp/src/csp_init.c \
../Libraries/libcsp/src/csp_io.c \
../Libraries/libcsp/src/csp_port.c \
../Libraries/libcsp/src/csp_promisc.c \
../Libraries/libcsp/src/csp_qfifo.c \
../Libraries/libcsp/src/csp_route.c \
../Libraries/libcsp/src/csp_service_handler.c \
../Libraries/libcsp/src/csp_services.c \
../Libraries/libcsp/src/csp_sfp.c 

OBJS += \
./Libraries/libcsp/src/csp_bridge.o \
./Libraries/libcsp/src/csp_buffer.o \
./Libraries/libcsp/src/csp_conn.o \
./Libraries/libcsp/src/csp_crc32.o \
./Libraries/libcsp/src/csp_debug.o \
./Libraries/libcsp/src/csp_dedup.o \
./Libraries/libcsp/src/csp_endian.o \
./Libraries/libcsp/src/csp_hex_dump.o \
./Libraries/libcsp/src/csp_iflist.o \
./Libraries/libcsp/src/csp_init.o \
./Libraries/libcsp/src/csp_io.o \
./Libraries/libcsp/src/csp_port.o \
./Libraries/libcsp/src/csp_promisc.o \
./Libraries/libcsp/src/csp_qfifo.o \
./Libraries/libcsp/src/csp_route.o \
./Libraries/libcsp/src/csp_service_handler.o \
./Libraries/libcsp/src/csp_services.o \
./Libraries/libcsp/src/csp_sfp.o 

C_DEPS += \
./Libraries/libcsp/src/csp_bridge.d \
./Libraries/libcsp/src/csp_buffer.d \
./Libraries/libcsp/src/csp_conn.d \
./Libraries/libcsp/src/csp_crc32.d \
./Libraries/libcsp/src/csp_debug.d \
./Libraries/libcsp/src/csp_dedup.d \
./Libraries/libcsp/src/csp_endian.d \
./Libraries/libcsp/src/csp_hex_dump.d \
./Libraries/libcsp/src/csp_iflist.d \
./Libraries/libcsp/src/csp_init.d \
./Libraries/libcsp/src/csp_io.d \
./Libraries/libcsp/src/csp_port.d \
./Libraries/libcsp/src/csp_promisc.d \
./Libraries/libcsp/src/csp_qfifo.d \
./Libraries/libcsp/src/csp_route.d \
./Libraries/libcsp/src/csp_service_handler.d \
./Libraries/libcsp/src/csp_services.d \
./Libraries/libcsp/src/csp_sfp.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/libcsp/src/%.o Libraries/libcsp/src/%.su Libraries/libcsp/src/%.cyclo: ../Libraries/libcsp/src/%.c Libraries/libcsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App/Src" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/App" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/Libraries/libcsp/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/srv/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/Driver/Inc" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983/common/lpldgen/include" -I"/media/maty/MyDisk/work/yspace/projects/csp/app_LTC2983/LTC2983" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-libcsp-2f-src

clean-Libraries-2f-libcsp-2f-src:
	-$(RM) ./Libraries/libcsp/src/csp_bridge.cyclo ./Libraries/libcsp/src/csp_bridge.d ./Libraries/libcsp/src/csp_bridge.o ./Libraries/libcsp/src/csp_bridge.su ./Libraries/libcsp/src/csp_buffer.cyclo ./Libraries/libcsp/src/csp_buffer.d ./Libraries/libcsp/src/csp_buffer.o ./Libraries/libcsp/src/csp_buffer.su ./Libraries/libcsp/src/csp_conn.cyclo ./Libraries/libcsp/src/csp_conn.d ./Libraries/libcsp/src/csp_conn.o ./Libraries/libcsp/src/csp_conn.su ./Libraries/libcsp/src/csp_crc32.cyclo ./Libraries/libcsp/src/csp_crc32.d ./Libraries/libcsp/src/csp_crc32.o ./Libraries/libcsp/src/csp_crc32.su ./Libraries/libcsp/src/csp_debug.cyclo ./Libraries/libcsp/src/csp_debug.d ./Libraries/libcsp/src/csp_debug.o ./Libraries/libcsp/src/csp_debug.su ./Libraries/libcsp/src/csp_dedup.cyclo ./Libraries/libcsp/src/csp_dedup.d ./Libraries/libcsp/src/csp_dedup.o ./Libraries/libcsp/src/csp_dedup.su ./Libraries/libcsp/src/csp_endian.cyclo ./Libraries/libcsp/src/csp_endian.d ./Libraries/libcsp/src/csp_endian.o ./Libraries/libcsp/src/csp_endian.su ./Libraries/libcsp/src/csp_hex_dump.cyclo ./Libraries/libcsp/src/csp_hex_dump.d ./Libraries/libcsp/src/csp_hex_dump.o ./Libraries/libcsp/src/csp_hex_dump.su ./Libraries/libcsp/src/csp_iflist.cyclo ./Libraries/libcsp/src/csp_iflist.d ./Libraries/libcsp/src/csp_iflist.o ./Libraries/libcsp/src/csp_iflist.su ./Libraries/libcsp/src/csp_init.cyclo ./Libraries/libcsp/src/csp_init.d ./Libraries/libcsp/src/csp_init.o ./Libraries/libcsp/src/csp_init.su ./Libraries/libcsp/src/csp_io.cyclo ./Libraries/libcsp/src/csp_io.d ./Libraries/libcsp/src/csp_io.o ./Libraries/libcsp/src/csp_io.su ./Libraries/libcsp/src/csp_port.cyclo ./Libraries/libcsp/src/csp_port.d ./Libraries/libcsp/src/csp_port.o ./Libraries/libcsp/src/csp_port.su ./Libraries/libcsp/src/csp_promisc.cyclo ./Libraries/libcsp/src/csp_promisc.d ./Libraries/libcsp/src/csp_promisc.o ./Libraries/libcsp/src/csp_promisc.su ./Libraries/libcsp/src/csp_qfifo.cyclo ./Libraries/libcsp/src/csp_qfifo.d ./Libraries/libcsp/src/csp_qfifo.o ./Libraries/libcsp/src/csp_qfifo.su ./Libraries/libcsp/src/csp_route.cyclo ./Libraries/libcsp/src/csp_route.d ./Libraries/libcsp/src/csp_route.o ./Libraries/libcsp/src/csp_route.su ./Libraries/libcsp/src/csp_service_handler.cyclo ./Libraries/libcsp/src/csp_service_handler.d ./Libraries/libcsp/src/csp_service_handler.o ./Libraries/libcsp/src/csp_service_handler.su ./Libraries/libcsp/src/csp_services.cyclo ./Libraries/libcsp/src/csp_services.d ./Libraries/libcsp/src/csp_services.o ./Libraries/libcsp/src/csp_services.su ./Libraries/libcsp/src/csp_sfp.cyclo ./Libraries/libcsp/src/csp_sfp.d ./Libraries/libcsp/src/csp_sfp.o ./Libraries/libcsp/src/csp_sfp.su

.PHONY: clean-Libraries-2f-libcsp-2f-src

