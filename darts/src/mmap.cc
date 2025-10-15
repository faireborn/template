#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <string>

#include "darts.h"

int main(int argc, char *argv[]) {
  if (argc != 2) exit(1);
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) exit(1);
  struct stat st;
  fstat(fd, &st);

  // Get file size
  const size_t length = st.st_size;

  // Map `dictionary.data` content to `data`
  char *data = (char *)mmap(0, length, PROT_READ, MAP_SHARED, fd, 0);

  close(fd);

  Darts::DoubleArray da;
  da.set_array(data, length / da.unit_size());

  constexpr int result_size = 512;
  Darts::DoubleArray::result_pair_type results[result_size];

  std::string line;
  std::cin >> line;
  const size_t size =
      da.commonPrefixSearch(line.data(), results, result_size, line.size());

  for (size_t i = 0; i < size; ++i) {
    std::cout.write(line.data(), results[i].length);
    std::cout << " " << results[i].value << std::endl;
  }

  // Unmap `data`
  munmap(data, length);
  return 0;
}
