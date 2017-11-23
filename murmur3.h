#ifndef __MURMUR__
#define __MURMUR__

#include <stdint.h>
#include <stddef.h>




unsigned long murmur3(const uint8_t* key, size_t len, unsigned long seed);

#endif
