#include <cstdint>
#include <iostream>
#include <vector>

class Fibonacci {
public:
  Fibonacci(uint64_t n) : memo_(n + 1, 0) {};
  ~Fibonacci() {};

  auto get(uint64_t n) {
    if (n < 2)
      return n;
    if (memo_[n])
      return memo_[n];
    return memo_[n] = get(n - 1) + get(n - 2);
  }

private:
  std::vector<uint64_t> memo_;
};

auto main() -> int {
  uint64_t n;
  std::cin >> n;

  auto fibonacci = Fibonacci(n);
  std::cout << fibonacci.get(n);
  return 0;
}
