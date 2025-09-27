#include "util.h"

#include <cmath>

namespace log_domain {
double LogSum(const std::vector<double> &xs) {
  if (xs.empty()) {
    return -1.0 * std::numeric_limits<double>::max();
  }
  double sum = xs.front();

  auto log_add = [](double xa, double xb) {
    if (xa > xb) {
      std::swap(xa, xb);
    }
    return xb + std::log1p(std::exp(xa - xb));
  };
  for (int i = 1; i < xs.size(); ++i) {
    sum = log_add(sum, xs[i]);
  }
  return sum;
}
}  // namespace log_domain
