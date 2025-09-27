#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

typedef uint32_t char32;

static constexpr uint32_t kUnicodeError =
    0xFFFD;  // REPLACEMENT CHARACTER (U+FFFD)

#endif
