#ifndef _SERVICE_ERR_CODES_H
#define _SERVICE_ERR_CODES_H

#include <stdint.h>

#ifndef SERVICE_ERR_PAYLOADS_OFFSET
#define SERVICE_ERR_PAYLOADS_OFFSET             (20)
#endif

#ifndef SERVICE_ERR_FILESYSTEM_OFFSET
#define SERVICE_ERR_FILESYSTEM_OFFSET           (100)
#endif

// common error codes

/*!
  \defgroup err_codes Common error codes.
  \{
*/

/*!
  \brief No error.
*/
#define SERVICE_ERR_NONE                        (0)

/*!
  \brief Unknown error - typically used when NULL pointer is detected where it really shouldn't be,
  or to catch else statements that make no sense.
*/
#define SERVICE_ERR_UNKNOWN                     (-1)

/*!
  \brief A magic number provided to some operation is invalid.
*/
#define SERVICE_ERR_INVALID_MAGIC_NUMBER        (-2)

/*!
  \brief Some provided argument is invalid or out of range.
*/
#define SERVICE_ERR_INVALID_ARG                 (-3)

/*!
  \brief Timed out waiting for some action to happen.
*/
#define SERVICE_ERR_TIMEOUT                     (-4)

/*!
  \brief Whoever was supposed to handle this is currently busy.
*/
#define SERVICE_ERR_BUSY                        (-5)

/*!
  \brief Failed to spawn thread.
*/
#define SERVICE_ERR_THREAD_SPAWN_FAILED         (-6)

/*!
  \brief Failed to find the specified callback.
*/
#define SERVICE_ERR_CB_NOT_FOUND                (-7)

/*!
  \brief Failed to allocate memory.
*/
#define SERVICE_ERR_MALLOC_FAILED               (-8)

/*!
  \brief Failed range check for some value (typically argument).
*/
#define SERVICE_ERR_VALUE_OUT_OF_RANGE          (-9)

/*!
  \brief This error originated from the payloads library.
*/
#define SERVICE_ERR_PAYLOADS(x)                 ((int8_t)(-SERVICE_ERR_PAYLOADS_OFFSET - (x)))

/*!
  \brief This error originated from the filesystem backend.
*/
#define SERVICE_ERR_FILESYSTEM(x)               ((int8_t)(-SERVICE_ERR_FILESYSTEM_OFFSET - (x)))

/*!
  \}
*/

#endif