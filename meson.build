# STM32U575xx Meson Build System
project('Azalka', 'c', 'cpp',
  version: '1.0.0',
  default_options: [
    'c_std=c11',
    'cpp_std=c++17',
    'b_staticpic=false',
    'buildtype=debug',
  ],
  meson_version: '>=1.0.0',
)

# Target-specific compile flags
target_cpu_flags = [
  '-mcpu=cortex-m33',
  '-mfpu=fpv5-sp-d16',
  '-mfloat-abi=hard',
  '-mthumb',
]

# Common compile flags
common_c_flags = [
  '-Wall',
  '-fdata-sections',
  '-ffunction-sections',
]

# Common C++ compile flags
common_cpp_flags = [
  '-Wall',
  '-fdata-sections',
  '-ffunction-sections',
  '-fno-exceptions',
  '-fno-rtti',
]

# Debug/Release flags are handled by meson's buildtype

# Target definitions
target_defines = [
  '-DUSE_HAL_DRIVER',
  '-DSTM32U575xx',
]

# Add DEBUG define for debug builds
if get_option('buildtype') == 'debug'
  target_defines += '-DDEBUG'
endif

# Linker flags
linker_script = meson.project_source_root() / 'STM32U575CITX_FLASH.ld'

target_link_flags = [
  '-T' + linker_script,
  '--specs=nano.specs',
  '-Wl,-Map=' + meson.project_name() + '.map',
  '-Wl,--gc-sections',
  '-Wl,--print-memory-usage',
]

# Startup file
startup_src = files('Core/Startup/startup_stm32u575citx.s')

# Include CMSIS (headers only)
subdir('Drivers/CMSIS')

# Include HAL Driver library
subdir('Drivers/STM32U5xx_HAL_Driver')

# Include FreeRTOS middleware
subdir('Middlewares/Third_Party/FreeRTOS')

# Include libcsp library
subdir('Libraries')

# Include Core application (after libraries so libcsp_dep is available)
subdir('Core')

# Include Application
subdir('App')

# Create the main executable
main_exe = executable(meson.project_name(),
  startup_src,
  c_args: target_cpu_flags + common_c_flags + target_defines,
  cpp_args: target_cpu_flags + common_cpp_flags + target_defines,
  link_args: target_cpu_flags + target_link_flags,
  link_with: [stm32_hal_lib],
  dependencies: [app_dep, core_dep, cmsis_dep, freertos_dep, libcsp_dep],
  name_suffix: 'elf',
)

# Generate binary file
objcopy = find_program('arm-none-eabi-objcopy', required: true)
main_bin = custom_target('binary',
  input: main_exe,
  output: meson.project_name() + '.bin',
  command: [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
  build_by_default: true,
)

# Generate hex file
main_hex = custom_target('hex',
  input: main_exe,
  output: meson.project_name() + '.hex',
  command: [objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
  build_by_default: true,
)

# Print size information
size = find_program('arm-none-eabi-size', required: false)
if size.found()
  custom_target('size',
    input: main_exe,
    output: 'size.txt',
    command: [size, '--format=berkeley', '@INPUT@'],
    capture: true,
    build_by_default: true,
  )
endif
