#ifndef UTILITIES_H
#define UTILITIES_H

#include "stdint.h"

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define _rw volatile
#define __w volatile
#define __r volatile const

#endif