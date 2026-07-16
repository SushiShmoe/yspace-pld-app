# Core Application Sources
# Contains the main application code and STM32CubeMX generated files

core_inc = include_directories('Inc')

# Application sources
core_sources = files(
  'Src/adc.c',
  'Src/app_freertos.c',
  'Src/gpio.c',
  'Src/i2c.c',
  'Src/main.c',
  'Src/rtc.c',
  'Src/rtc_srv.c',
  'Src/stm32u5xx_it.c',
  'Src/stm32u5xx_hal_msp.c',
  'Src/stm32u5xx_hal_timebase_tim.c',
  'Src/syscalls.c',
  'Src/sysmem.c',
  'Src/system_stm32u5xx.c',
)

# Create a dependency that includes sources and headers
# The sources will be compiled into the main executable
core_dep = declare_dependency(
  sources: core_sources,
  include_directories: core_inc,
  dependencies: [stm32_hal_dep, libcsp_dep],
)
