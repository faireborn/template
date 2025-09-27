#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <vector>

#include "common.h"

namespace string_util {

inline size_t OneCharLen(const char *src) {
  return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[(*src & 0xFF) >> 4];
}

// Return (x & 0xC0) == 0x80;
// Since trail bytes are always in [0x80, 0xBF], we can optimize:
inline bool IsTrailByte(char x) { return static_cast<signed char>(x) < -0x40; }

inline bool IsValidCodepoint(char32 c) {
  return (static_cast<uint32_t>(c) < 0xD800) || (c >= 0xE000 && c <= 0x10FFFF);
}

bool IsStructurallyValid(std::string str);

char32 DecodeUTF8(const char *begin, const char *end, size_t *mblen);
inline char32 DecodeUTF8(std::string input, size_t *mblen) {
  return DecodeUTF8(input.data(), input.data() + input.length(), mblen);
}

size_t EncodeUTF8(char32 c, char *output);

inline size_t UTF8Length(char32 c) {
  if (c <= 0x7F) {
    return 1;
  }
  if (c <= 0x7FF) {
    return 2;
  }

  // If `c` is out of range, we consider it as kUnicodeError, which is 3 bytes.
  if (c <= 0xFFFF || c > 0x10FFFF) {
    return 3;
  }
  return 4;
}

}  // namespace string_util

namespace log_domain {

double LogSum(const std::vector<double> &xs);

}  // namespace log_domain

#endif
