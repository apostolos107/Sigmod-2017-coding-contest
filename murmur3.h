#ifndef __MURMUR__
#define __MURMUR__

#include <stdint.h>
#include <stddef.h>

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;


uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);

#endif
