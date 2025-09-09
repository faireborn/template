#include <iostream>
#include <vector>

auto main() -> int {
  int L, n;
  std::cin >> L >> n;
  std::vector<int> x(n);

  for (auto &e : x)
    std::cin >> e;

  int min_t{0};
  for (const auto &e : x)
    min_t = std::max(min_t, std::min(e, L - e));

  int max_t{0};
  for (const auto &e : x)
    max_t = std::max(max_t, std::max(e, L - e));

  std::cout << min_t << std::endl << max_t;
  return 0;
}
