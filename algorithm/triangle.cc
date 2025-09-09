#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto &e : a)
    std::cin >> e;

  std::sort(a.begin(), a.end());

  int max_perimeter{0};
  for (int i = 2; i < n; i++) {
    if (a[i] < a[i - 1] + a[i - 2])
      max_perimeter = std::max(max_perimeter, a[i] + a[i - 1] + a[i - 2]);
  }
  std::cout << max_perimeter;
  return 0;
}
