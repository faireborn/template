#include <iostream>
#include <vector>

int n, k;

bool dfs(int i, int sum, std::vector<int> a) {
  if (i == n)
    return sum == k;
  if (dfs(i + 1, sum, a)) // don't use a[i]
    return true;
  if (dfs(i + 1, sum + a[i], a)) // use a[i]
    return true;
  return false;
}

auto main() -> int {
  std::cin >> n;
  std::vector<int> a(n, 0);
  for (auto &e : a)
    std::cin >> e;
  std::cin >> k;

  if (dfs(0, 0, a))
    std::cout << "Yes";
  else
    std::cout << "No";
  return 0;
}
