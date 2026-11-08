#ifndef SHAWARMAOS_STDINT_H
#define SHAWARMAOS_STDINT_H

// Types
// Unsigned Integer 8-64 bit
typedef __UINT8_TYPE__     uint8_t;
typedef __UINT16_TYPE__    uint16_t;
typedef __UINT32_TYPE__    uint32_t;
typedef __UINT64_TYPE__    uint64_t;

// Signed Integer 8-64 bit
typedef __INT8_TYPE__      int8_t;
typedef __INT16_TYPE__     int16_t;
typedef __INT32_TYPE__     int32_t;
typedef __INT64_TYPE__     int64_t;

// Pointer-width Integer
typedef __INTPTR_TYPE__    intptr_t;
typedef __UINTPTR_TYPE__   uintptr_t;

// Macro Constants

// Signed Integers: minimum value
#define INT8_MIN  (-__INT8_MAX__ - 1)
#define INT16_MIN (-__INT16_MAX__ - 1)
#define INT32_MIN (-__INT32_MAX__ - 1)
#define INT64_MIN (-__INT64_MAX__ - 1)

// Signed Integers: maximum value
#define INT8_MAX  __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__

// Unsigned Integers: minimum value
#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0U
#define UINT64_MIN 0ULL

// Unsigned Integers: maximum value
#define UINT8_MAX  __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__

// Pointer-width Integers: min and max value
#define INTPTR_MIN  (-__INTPTR_MAX__ - 1)
#define INTPTR_MAX  __INTPTR_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__

#define SIZE_MAX    __SIZE_MAX__


#endif /* SHAWARMAOS_STDINT_H */
