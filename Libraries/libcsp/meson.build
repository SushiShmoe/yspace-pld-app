project('lib-csp', 'c', version : '0.1')

is_freertos = (get_option('csp_platform') == 'freertos') or (get_option('csp_platform') == 'stm32h7')
is_posix = get_option('csp_platform') == 'posix'
is_windows = get_option('csp_platform') == 'windows'
is_macosx = get_option('csp_platform') == 'macosx'

# Always included CSP files
csp_src = files(
  'src/csp_bridge.c',
  'src/csp_buffer.c',
  'src/csp_conn.c',
  'src/csp_endian.c',
  'src/csp_hex_dump.c',
  'src/csp_iflist.c',
  'src/csp_init.c',
  'src/csp_io.c',
  'src/csp_port.c',
  'src/csp_qfifo.c',
  'src/csp_route.c',
  'src/csp_service_handler.c',
  'src/csp_services.c',
  'src/csp_sfp.c',
  'src/arch/csp_system.c',
  'src/arch/csp_time.c',
  'src/interfaces/csp_if_lo.c',
  'src/rtable/csp_rtable.c',
  'src/transport/csp_udp.c',
)

csp_deps = []
csp_inc = include_directories('include')

# Optional compilation (use to save space in embedded)
if get_option('csp_debug')
  csp_src += files('src/csp_debug.c')
endif

if get_option('csp_use_hmac')
  csp_src += files(
    'src/crypto/csp_hmac.c',
    'src/crypto/csp_sha1.c',
  )
endif

if get_option('csp_use_xtea')
  csp_src += files(
    'src/crypto/csp_xtea.c',
    'src/crypto/csp_sha1.c',
  )
endif

if get_option('csp_use_rdp')
  csp_src += files('src/transport/csp_rdp.c')
endif

if get_option('csp_use_crc32')
  csp_src += files('src/csp_crc32.c')
endif

if get_option('csp_use_dedup')
  csp_src += files('src/csp_dedup.c')
endif

if get_option('csp_use_promisc')
  csp_src += files('src/csp_promisc.c')
endif

# Routing table variant
if get_option('csp_use_cidr_rtable')
  csp_src += files('src/rtable/csp_rtable_cidr.c')
else
  csp_src += files('src/rtable/csp_rtable_static.c')
endif

# Architecture-specific files
if is_freertos
  csp_src += files(
    'src/arch/freertos/csp_clock.c',
    'src/arch/freertos/csp_malloc.c',
    'src/arch/freertos/csp_queue.c',
    'src/arch/freertos/csp_semaphore.c',
    'src/arch/freertos/csp_system.c',
    'src/arch/freertos/csp_thread.c',
    'src/arch/freertos/csp_time.c',
  )
elif is_posix
  csp_src += files(
    'src/arch/posix/csp_clock.c',
    'src/arch/posix/csp_malloc.c',
    'src/arch/posix/csp_queue.c',
    'src/arch/posix/csp_semaphore.c',
    'src/arch/posix/csp_system.c',
    'src/arch/posix/csp_thread.c',
    'src/arch/posix/csp_time.c',
    'src/arch/posix/pthread_queue.c',
  )
  csp_deps += dependency('threads')
elif is_windows
  csp_src += files(
    'src/arch/windows/csp_clock.c',
    'src/arch/windows/csp_malloc.c',
    'src/arch/windows/csp_queue.c',
    'src/arch/windows/csp_semaphore.c',
    'src/arch/windows/csp_system.c',
    'src/arch/windows/csp_thread.c',
    'src/arch/windows/csp_time.c',
    'src/arch/windows/windows_queue.c',
  )
elif is_macosx
  csp_src += files(
    'src/arch/macosx/csp_clock.c',
    'src/arch/macosx/csp_malloc.c',
    'src/arch/macosx/csp_queue.c',
    'src/arch/macosx/csp_semaphore.c',
    'src/arch/macosx/csp_system.c',
    'src/arch/macosx/csp_thread.c',
    'src/arch/macosx/csp_time.c',
    'src/arch/macosx/pthread_queue.c',
  )
endif

# CAN driver
if get_option('csp_use_ifc_can')
  csp_src += files(
    'src/interfaces/csp_if_can.c',
    'src/interfaces/csp_if_can_pbuf.c',
  )

  if get_option('csp_can_socketcan')
    if not is_posix
      error('CSP arch is not Posix, can\'t use SocketCAN driver!')
    endif
    csp_src += files('src/drivers/can/can_socketcan.c')
    csp_deps += dependency('libsocketcan')
  endif
endif

# I2C driver
if get_option('csp_use_ifc_i2c')
  csp_src += files('src/interfaces/csp_if_i2c.c')
endif

# USART driver
if get_option('csp_use_ifc_kiss')
  csp_src += files(
    'src/interfaces/csp_if_kiss.c',
    'src/drivers/usart/usart_kiss.c',
  )

  if get_option('csp_usart_linux')
    if not is_posix
      error('CSP arch is not Posix, can\'t use Linux USART driver!')
    endif
    csp_src += files('src/drivers/usart/usart_linux.c')
  endif

  if get_option('csp_usart_windows')
    if not is_windows
      error('CSP arch is not Windows, can\'t use Windows USART driver!')
    endif
    csp_src += files('src/drivers/usart/usart_windows.c')
  endif
endif

if get_option('csp_platform') == 'stm32h7'
  stm32h7 = dependency('stm32h7-hal-core')
  csp_deps += stm32h7
endif

csp_config = configuration_data()
csp_config.set10('CSP_FREERTOS', is_freertos)
csp_config.set10('CSP_POSIX', is_posix)
csp_config.set10('CSP_WINDOWS', is_windows)
csp_config.set10('CSP_MACOSX', is_macosx)
csp_config.set10('CSP_I2C_FRAME_PACKED', get_option('csp_i2c_frame_packed'))
csp_config.set10('CSP_DEBUG', get_option('csp_debug'))
csp_config.set10('CSP_DEBUG_TIMESTAMP', false)
csp_config.set10('CSP_USE_EXTERNAL_DEBUG', get_option('csp_use_external_debug'))
csp_config.set10('CSP_USE_CUSTOM_PRINTF', get_option('csp_use_custom_printf'))
loglevel = get_option('csp_log_level')
csp_config.set10('CSP_LOG_LEVEL_DEBUG', loglevel == 'debug')
csp_config.set10('CSP_LOG_LEVEL_INFO', loglevel == 'info' or loglevel == 'debug')
csp_config.set10('CSP_LOG_LEVEL_WARN', loglevel == 'warn' or loglevel == 'info' or loglevel == 'debug')
csp_config.set10('CSP_LOG_LEVEL_ERROR', loglevel == 'error' or loglevel == 'warn' or loglevel == 'info' or loglevel == 'debug')
csp_config.set10('CSP_USE_RDP', get_option('csp_use_rdp'))
csp_config.set10('CSP_USE_RDP_FAST_CLOSE', get_option('csp_use_rdp_fast_close'))
csp_config.set10('CSP_USE_CRC32', get_option('csp_use_crc32'))
csp_config.set10('CSP_USE_HMAC', get_option('csp_use_hmac'))
csp_config.set10('CSP_USE_XTEA', get_option('csp_use_xtea'))
csp_config.set10('CSP_USE_PROMISC', get_option('csp_use_promisc'))
csp_config.set10('CSP_USE_QOS', get_option('csp_use_qos'))
csp_config.set10('CSP_USE_DEDUP', get_option('csp_use_dedup'))
csp_config.set10('CSP_USE_CIDR_RTABLE', get_option('csp_use_cidr_rtable'))
csp_config.set10('CSP_USE_IFC_I2C', get_option('csp_use_ifc_i2c'))
csp_config.set10('CSP_USE_IFC_KISS', get_option('csp_use_ifc_kiss'))
csp_config.set10('CSP_USART_WINDOWS', get_option('csp_usart_windows'))
csp_config.set10('CSP_USART_LINUX', get_option('csp_usart_linux'))
csp_config.set10('CSP_USE_IFC_CAN', get_option('csp_use_ifc_can'))
csp_config.set10('CSP_CAN_SOCKETCAN', get_option('csp_can_socketcan'))
csp_config.set10('CSP_HAVE_LIBSOCKETCAN', get_option('csp_have_libsocketcan'))
csp_config.set10('CSP_HAVE_SSCANF', get_option('csp_have_sscanf'))
csp_config.set10('CSP_HAVE_RAND', get_option('csp_have_rand'))

csp_lib = library(
  'csp',
  csp_src,
  dependencies : csp_deps,
  include_directories : csp_inc,
  install : true
)

csp_dep = declare_dependency(
  include_directories : csp_inc,
  dependencies : csp_deps,
  link_with : csp_lib
)
meson.override_dependency('csp', csp_dep)

pkgconfig = import('pkgconfig')
pkgconfig.generate(csp_lib)

install_subdir('include/csp', install_dir : get_option('includedir'), exclude_files : 'meson.build')

subdir('include/csp')

if get_option('enable_python3_bindings')
	py = import('python').find_installation('python3')
	# py.dependency() doesn't work with version constraint. Use plain
	# dependency() instead
	pydep = dependency('python3', version : '>=3.10', required : true)
	py.extension_module('libcsp_py3', 'src/bindings/python/pycsp.c',
                    	dependencies : [csp_dep, pydep],
                    	install : true)
endif
