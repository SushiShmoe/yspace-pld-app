# Core Application Sources
# Contains the main application code and STM32CubeMX generated files

app_inc = include_directories('Inc')

# Application sources
app_sources = files(
  'Src/antracit_csp_handlers.c',
  'Src/app.c',
  'Src/app_csp.c',
  'Src/cJSON.c',
  'Src/payloads.c',
  'Src/pld_antracit.c',
)

# Create a dependency that includes sources and headers
# The sources will be compiled into the main executable
app_dep = declare_dependency(
  sources: app_sources,
  include_directories: app_inc,
  dependencies: [stm32_hal_dep, libcsp_dep, core_dep],
)
