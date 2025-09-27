#ifndef UTIL_H_
#define UTIL_H_

#include <vector>

namespace string_util {

inline size_t OneCharLen(const char *src) {
  return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[(*src & 0xFF) >> 4];
}
}  // namespace string_util

namespace log_domain {

double LogSum(const std::vector<double> &xs);

}  // namespace log_domain

#endif
