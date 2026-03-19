cmake_minimum_required(VERSION 3.13)

project(lib-csp)

# freertos,posix,windows,macos
option(CSP_FREERTOS "Platform is FreeRTOS" OFF)
option(CSP_POSIX    "Platform is POSIX" OFF)
option(CSP_WINDOWS  "Platform is Windows" OFF)
option(CSP_MACOSX   "Platform is MacOS" OFF)

# Translate architecture to individual flags
if(NOT (CSP_FREERTOS OR CSP_POSIX OR CSP_WINDOWS OR CSP_MACOSX))
    message(FATAL_ERROR "Bad CSP_ARCH value!")
endif()

option(CSP_I2C_FRAME_PACKED "Make the I2C frame packed" OFF) # Workaround for NanoMind OBC firmware

option(CSP_DEBUG "Debug logging enabled" ON)
option(CSP_USE_EXTERNAL_DEBUG "Do not use the bundled csp_debug.c" OFF)
option(CSP_USE_CUSTOM_PRINTF  "Use external csp_printf implementations instead of stdlib" OFF)

# Set the finest level to log to ON, higher will be enabled automatically
option(CSP_LOG_LEVEL_DEBUG "Enable debug level logging" OFF)
option(CSP_LOG_LEVEL_INFO  "Enable info level logging"  OFF)
option(CSP_LOG_LEVEL_WARN  "Enable warn level logging"  OFF)
option(CSP_LOG_LEVEL_ERROR "Enable error level logging" OFF)

# Expand CSP_LOG_LEVEL to individual flags
if(CSP_LOG_LEVEL_DEBUG)
    set(CSP_LOG_LEVEL_DEBUG ON)
    set(CSP_LOG_LEVEL_INFO  ON)
    set(CSP_LOG_LEVEL_WARN  ON)
    set(CSP_LOG_LEVEL_ERROR ON)
elseif(CSP_LOG_LEVEL_INFO)
    set(CSP_LOG_LEVEL_INFO  ON)
    set(CSP_LOG_LEVEL_WARN  ON)
    set(CSP_LOG_LEVEL_ERROR ON)
elseif(CSP_LOG_LEVEL_WARN)
    set(CSP_LOG_LEVEL_WARN  ON)
    set(CSP_LOG_LEVEL_ERROR ON)
elseif(CSP_LOG_LEVEL_ERROR)
    set(CSP_LOG_LEVEL_ERROR ON)
else()
    # Default to all ON
    set(CSP_LOG_LEVEL_DEBUG ON)
    set(CSP_LOG_LEVEL_INFO  ON)
    set(CSP_LOG_LEVEL_WARN  ON)
    set(CSP_LOG_LEVEL_ERROR ON)
endif()


option(CSP_USE_RDP      "Support RDP" ON)
option(CSP_USE_RDP_FAST_CLOSE  "Use RDP fast close mode (if RDP used)" ON)
option(CSP_USE_CRC32    "Support CRC32" ON)
option(CSP_USE_HMAC     "Support HMAC" ON)
option(CSP_USE_XTEA     "Support XTEA" ON)
option(CSP_USE_PROMISC  "Support promiscuous mode" ON)
option(CSP_USE_QOS      "Support QoS" ON)
option(CSP_USE_DEDUP    "Use deduplication" OFF)

option(CSP_USE_CIDR_RTABLE "Use CIDR routing table (OFF = static)" ON)

option(CSP_USE_IFC_I2C "Use I2C interface" ON)

option(CSP_USE_IFC_KISS "Use KISS interface" OFF)
option(CSP_USART_WINDOWS "Use Windows USART driver" OFF)
option(CSP_USART_LINUX "Use Linux USART driver" OFF)

option(CSP_USE_IFC_CAN "Use CAN interface" OFF)
option(CSP_CAN_SOCKETCAN "Use the built-in socketcan driver" OFF)
option(CSP_HAVE_LIBSOCKETCAN    "Use socketcan library" OFF)
option(CSP_HAVE_SSCANF    "Use sscanf for routing table parsing" ON)
option(CSP_HAVE_RAND     "Use rand(). Disable to use a custom PRNG" ON)


# Always included CSP files
file(GLOB CSP_SOURCES
        "src/csp_bridge.c"
        "src/csp_buffer.c"
        "src/csp_conn.c"
        "src/csp_endian.c"
        "src/csp_hex_dump.c"
        "src/csp_iflist.c"
        "src/csp_init.c"
        "src/csp_io.c"
        "src/csp_port.c"
        "src/csp_qfifo.c"
        "src/csp_route.c"
        "src/csp_service_handler.c"
        "src/csp_services.c"
        "src/csp_sfp.c"
        "src/arch/csp_system.c"
        "src/arch/csp_time.c"
        "src/interfaces/csp_if_lo.c"
        "src/rtable/csp_rtable.c"
        "src/transport/csp_udp.c"
)

# Optional compilation (use to save space in embedded)
if(CSP_DEBUG)
    list(APPEND CSP_SOURCES "src/csp_debug.c")
endif()

if(CSP_USE_HMAC)
    list(APPEND CSP_SOURCES "src/crypto/csp_hmac.c")
    list(APPEND CSP_SOURCES "src/crypto/csp_sha1.c")
endif()

if(CSP_USE_XTEA)
    list(APPEND CSP_SOURCES "src/crypto/csp_xtea.c")
    list(APPEND CSP_SOURCES "src/crypto/csp_sha1.c")
endif()

if(CSP_USE_RDP)
    list(APPEND CSP_SOURCES "src/transport/csp_rdp.c")
endif()

if(CSP_USE_CRC32)
    list(APPEND CSP_SOURCES "src/csp_crc32.c")
endif()

if(CSP_USE_DEDUP)
    list(APPEND CSP_SOURCES "src/csp_dedup.c")
endif()

if(CSP_USE_PROMISC)
    list(APPEND CSP_SOURCES "src/csp_promisc.c")
endif()

# Routing table variant
if(CSP_USE_CIDR_RTABLE)
    list(APPEND CSP_SOURCES "src/rtable/csp_rtable_cidr.c")
else()
    list(APPEND CSP_SOURCES "src/rtable/csp_rtable_static.c")
endif()

# Architecture-specific files
if(CSP_FREERTOS)
    file(GLOB GLOB_RESULT "src/arch/freertos/*.c")
    list(APPEND CSP_SOURCES ${GLOB_RESULT})
elseif(CSP_POSIX)
    file(GLOB GLOB_RESULT "src/arch/posix/*.c")
    list(APPEND CSP_SOURCES ${GLOB_RESULT})
elseif(CSP_WINDOWS)
    file(GLOB GLOB_RESULT "src/arch/windows/*.c")
    list(APPEND CSP_SOURCES ${GLOB_RESULT})
elseif(CSP_MACOSX)
    file(GLOB GLOB_RESULT "src/arch/macosx/*.c")
    list(APPEND CSP_SOURCES ${GLOB_RESULT})
endif()

# CAN driver
if(CSP_USE_IFC_CAN)
    list(APPEND CSP_SOURCES "src/interfaces/csp_if_can.c")
    list(APPEND CSP_SOURCES "src/interfaces/csp_if_can_pbuf.c")

    if(CSP_CAN_SOCKETCAN)
        if(NOT CSP_POSIX)
            message(FATAL_ERROR "CSP arch is not Posix, can't use SocketCAN driver!")
        endif()
        list(APPEND CSP_SOURCES "src/drivers/can/can_socketcan.c")
    endif()
endif()

# I2C driver
if(CSP_USE_IFC_I2C)
    list(APPEND CSP_SOURCES "src/interfaces/csp_if_i2c.c")
endif()

# USART driver
if(CSP_USE_IFC_KISS)
    list(APPEND CSP_SOURCES "src/interfaces/csp_if_kiss.c")

    if(CSP_USART_LINUX)
        if(NOT CSP_POSIX)
            message(FATAL_ERROR "CSP arch is not Posix, can't use Linux USART driver!")
        endif()

        list(APPEND CSP_SOURCES "src/drivers/usart/usart_linux.c")
    endif()

    if(CSP_USART_WINDOWS)
        if(NOT CSP_WINDOWS)
            message(FATAL_ERROR "CSP arch is not Windows, can't use Windows USART driver!")
        endif()

        list(APPEND CSP_SOURCES "src/drivers/usart/usart_windows.c")
    endif()

    list(APPEND CSP_SOURCES "src/drivers/usart/usart_kiss.c")
endif()

# Generate config header file
configure_file(
        "include/csp/csp_autoconfig.h.in"
        "include/csp/csp_autoconfig.h"
)

option(CSP_SHARED_LIBRARY OFF)
set(LIB_TYPE STATIC)
if(CSP_SHARED_LIBRARY)
    set(LIB_TYPE SHARED)
endif()
add_library(csp ${LIB_TYPE} ${CSP_SOURCES})

target_include_directories(csp
        PUBLIC "include" "${CMAKE_CURRENT_BINARY_DIR}/include"  # this is where the generated config header is placed
        PRIVATE "src"
)

if(ESP_PLATFORM)
    target_link_libraries(csp idf::freertos)
elseif(CSP_POSIX OR CSP_MACOS)
    target_link_libraries(csp pthread)
    if(CSP_SHARED_LIBRARY)
        target_link_libraries(csp socketcan)
    endif()
elseif(DEFINED NANOMIND_PLATFORM)
    target_link_libraries(csp asf)
elseif(DEFINED STM32H7_PLATFORM)
    target_link_libraries(csp stm32h7-hal-core)
elseif(DEFINED DEEPTHOUGHT_PLATFORM)
    target_link_libraries(csp libasf4)
endif()
