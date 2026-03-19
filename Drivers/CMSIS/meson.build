# CMSIS - Cortex Microcontroller Software Interface Standard
# This provides header-only dependencies for ARM Cortex-M cores

cmsis_core_inc = include_directories('Include')
cmsis_device_inc = include_directories('Device/ST/STM32U5xx/Include')

# CMSIS is header-only, so we create a dependency object
cmsis_dep = declare_dependency(
  include_directories: [cmsis_core_inc, cmsis_device_inc],
)
