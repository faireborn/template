#include <iostream>
#include <string>
#include <vector>

#include "darts.h"

size_t OneCharLen(const char *c) {
  return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[(*c & 0xFF) >> 4];
}

int main(int argc, char *argv[]) {
  if (argc != 2) exit(1);
  Darts::DoubleArray da;
  da.open(argv[1]);

  constexpr int result_size = 512;
  Darts::DoubleArray::result_pair_type results[result_size];

  std::string line;

  while (std::getline(std::cin, line)) {
    const char *begin = line.data();
    const char *end = line.data() + line.size();

    while (begin < end) {
      const size_t size = da.commonPrefixSearch(
          begin, results, result_size, static_cast<size_t>(begin - end));

      for (size_t i = 0; i < size; ++i) {
        std::cout.write(begin, results[i].length);
        std::cout << " " << results[i].value << std::endl;
      }
      begin += OneCharLen(begin);
    }
  }

  return 0;
}
