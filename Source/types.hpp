#pragma once

#include <stdint.h>

#ifdef _WIN64
using Address = uint64_t;
#else
using Address = uint32_t;
#endif