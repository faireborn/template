#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "darts.h"

int main(int argc, char **argv) {
  std::string line;
  std::vector<std::string> dic;
  std::ifstream ifs("dic.txt");
  while (std::getline(ifs, line)) {
    dic.emplace_back(line);
  }

  std::sort(dic.begin(), dic.end());

  std::vector<const char *> key;
  std::vector<int> value;
  for (int i = 0; i < dic.size(); ++i) {
    key.emplace_back(dic[i].c_str());
    value.emplace_back(i);
  }

  Darts::DoubleArray da;
  da.build(key.size(), const_cast<char **>(key.data()), nullptr, value.data());
  da.save("dictionary.data");

  return 0;
}
