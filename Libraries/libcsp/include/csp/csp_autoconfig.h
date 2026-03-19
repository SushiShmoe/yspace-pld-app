#ifndef W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF
#define W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF

#define GIT_REV "v1.6+vzlu"

#define CSP_FREERTOS 1
#define CSP_POSIX 0
#define CSP_WINDOWS 0
#define CSP_MACOSX 0

#define CSP_DEBUG 1
#define CSP_DEBUG_TIMESTAMP 0
#define CSP_USE_RDP 1
#define CSP_USE_RDP_FAST_CLOSE 1
#define CSP_USE_CRC32 1
#define CSP_USE_HMAC 1
#define CSP_USE_XTEA 1
#define CSP_USE_PROMISC 1
#define CSP_USE_QOS 1
#define CSP_USE_DEDUP 0
#define CSP_USE_EXTERNAL_DEBUG 0
#define CSP_USE_CUSTOM_PRINTF 0
#define CSP_HAVE_LIBSOCKETCAN 0
#define CSP_I2C_FRAME_PACKED 0
#define CSP_HAVE_SSCANF 1
#define CSP_HAVE_RAND 1
#define csp_use_cidr_rtable 0

#define CSP_LOG_LEVEL_DEBUG 1
#define CSP_LOG_LEVEL_INFO 1
#define CSP_LOG_LEVEL_WARN 1
#define CSP_LOG_LEVEL_ERROR 1

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define CSP_BIG_ENDIAN 1
#else
    #define CSP_LITTLE_ENDIAN 1
#endif

#define CSP_HAVE_STDBOOL_H 1
#define LIBCSP_VERSION "1.6"

/* Not used by CSP - only for external feature checking */
#define CSP_USE_CIDR_RTABLE 0
#define LIBCSP_VZLU 1

#endif /* W_INCLUDE_CSP_CSP_AUTOCONFIG_H_WAF */
