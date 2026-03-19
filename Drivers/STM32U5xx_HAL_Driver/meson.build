# STM32U5xx HAL Driver Library
# This builds the Hardware Abstraction Layer as a static library

hal_inc = include_directories('Inc', 'Inc/Legacy')

# HAL configuration header is in Core/Inc (project-specific config)
hal_conf_inc = include_directories('../../Core/Inc')

# HAL Driver source files - add/remove as needed based on your project
hal_sources = files(
  # Core HAL
  'Src/stm32u5xx_hal.c',
  'Src/stm32u5xx_hal_cortex.c',
  
  # RCC - Clock configuration
  'Src/stm32u5xx_hal_rcc.c',
  'Src/stm32u5xx_hal_rcc_ex.c',
  
  # GPIO
  'Src/stm32u5xx_hal_gpio.c',
  
  # Flash
  'Src/stm32u5xx_hal_flash.c',
  'Src/stm32u5xx_hal_flash_ex.c',
  
  # DMA
  'Src/stm32u5xx_hal_dma.c',
  'Src/stm32u5xx_hal_dma_ex.c',
  
  # Power management
  'Src/stm32u5xx_hal_pwr.c',
  'Src/stm32u5xx_hal_pwr_ex.c',
  
  # EXTI - External interrupts
  'Src/stm32u5xx_hal_exti.c',
  
  # I2C
  'Src/stm32u5xx_hal_i2c.c',
  'Src/stm32u5xx_hal_i2c_ex.c',
  
  # Security
  'Src/stm32u5xx_hal_gtzc.c',
  'Src/stm32u5xx_hal_icache.c',

  # USART
  # 'Src/stm32u5xx_hal_uart.c',
  # 'Src/stm32u5xx_hal_uart_ex.c',

  # ADC
  'Src/stm32u5xx_hal_adc.c',
  'Src/stm32u5xx_hal_adc_ex.c',
  
  # TIM - Timers
  'Src/stm32u5xx_hal_tim.c',
  'Src/stm32u5xx_hal_tim_ex.c',
  
  # RTC - Real-Time Clock
  'Src/stm32u5xx_hal_rtc.c',
  'Src/stm32u5xx_hal_rtc_ex.c',

  # SPI
  # 'Src/stm32u5xx_hal_spi.c',
  # 'Src/stm32u5xx_hal_spi_ex.c',
  
  # Uncomment below as needed for your project:
  # 'Src/stm32u5xx_hal_adc.c',
  # 'Src/stm32u5xx_hal_adc_ex.c',
  
)

# Build HAL as a static library
stm32_hal_lib = static_library('stm32_hal',
  hal_sources,
  c_args: target_cpu_flags + common_c_flags + target_defines,
  include_directories: [hal_inc, hal_conf_inc],
  dependencies: [cmsis_dep],
  pic: false,
)

# Create a dependency for the HAL that includes its headers
stm32_hal_dep = declare_dependency(
  include_directories: hal_inc,
  link_with: stm32_hal_lib,
  dependencies: [cmsis_dep],
)
