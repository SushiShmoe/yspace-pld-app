# External Libraries
# Third-party libraries for the project

# libcsp - CubeSat Space Protocol
# Build library sources directly

libcsp_inc = include_directories('libcsp/include')

libcsp_src = files(
  'libcsp/src/csp_bridge.c',
  'libcsp/src/csp_buffer.c',
  'libcsp/src/csp_conn.c',
  'libcsp/src/csp_crc32.c',
  'libcsp/src/csp_debug.c',
  'libcsp/src/csp_endian.c',
  'libcsp/src/csp_hex_dump.c',
  'libcsp/src/csp_iflist.c',
  'libcsp/src/csp_init.c',
  'libcsp/src/csp_io.c',
  'libcsp/src/csp_port.c',
  'libcsp/src/csp_promisc.c',
  'libcsp/src/csp_qfifo.c',
  'libcsp/src/csp_route.c',
  'libcsp/src/csp_service_handler.c',
  'libcsp/src/csp_services.c',
  'libcsp/src/csp_sfp.c',
  'libcsp/src/arch/csp_system.c',
  'libcsp/src/arch/csp_time.c',
  'libcsp/src/arch/freertos/csp_clock.c',
  'libcsp/src/arch/freertos/csp_malloc.c',
  'libcsp/src/arch/freertos/csp_queue.c',
  'libcsp/src/arch/freertos/csp_semaphore.c',
  'libcsp/src/arch/freertos/csp_system.c',
  'libcsp/src/arch/freertos/csp_thread.c',
  'libcsp/src/arch/freertos/csp_time.c',
  'libcsp/src/crypto/csp_hmac.c',
  'libcsp/src/crypto/csp_sha1.c',
  'libcsp/src/crypto/csp_xtea.c',
  'libcsp/src/interfaces/csp_if_lo.c',
  # 'libcsp/src/interfaces/csp_if_usart.c',
  'libcsp/src/interfaces/csp_if_i2c.c',
  'libcsp/src/rtable/csp_rtable.c',
  'libcsp/src/rtable/csp_rtable_static.c',
  'libcsp/src/transport/csp_rdp.c',
  'libcsp/src/transport/csp_udp.c',
  # 'libcsp/src/drivers/usart/driver_usart.c',
  'libcsp/src/drivers/i2c/driver_i2c.c'
)

# Build libcsp as a static library
libcsp_lib = static_library('csp',
  libcsp_src,
  include_directories: [libcsp_inc, freertos_inc, freertos_config_inc, cmsis_core_inc, cmsis_device_inc, hal_inc],
  c_args: target_cpu_flags + common_c_flags + target_defines + [
    '-DCSP_FREERTOS=1',
    '-DCSP_DEBUG=1',
    '-DCSP_USE_RDP=1',
    '-DCSP_USE_CRC32=1',
    '-DCSP_USE_HMAC=1',
    '-DCSP_USE_XTEA=1',
    '-DCSP_USE_QOS=1',
    '-DCSP_USE_PROMISC=1',
  ],
  pic: false,
)

# Declare libcsp dependency
libcsp_dep = declare_dependency(
  include_directories: libcsp_inc,
  link_with: libcsp_lib,
)