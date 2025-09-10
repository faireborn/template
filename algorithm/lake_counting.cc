#include <iostream>
#include <print>
#include <vector>

/* -------------------
      w........ww.
      .www.....www
      ....ww...ww.
      .........ww.
      .........w..
      ..w......w..
      .w.w.....ww.
      w.w.w.....w.
      .w.w......w.
      ..w.......w.
------------------- */

int n, m;
void dfs(int i, int j, std::vector<std::vector<char>> &garden) {
  garden[i][j] = '.';

  for (int ii = -1; ii <= 1; ii++) {
    for (int jj = -1; jj <= 1; jj++) {
      auto next_i{i + ii};
      auto next_j{j + jj};

      if (0 <= next_i && next_i < n && 0 <= next_j && next_j < m &&
          garden[next_i][next_j] == 'w')
        dfs(next_i, next_j, garden);
    }
  }
}

auto main() -> int {
  std::cin >> n >> m;
  std::vector<std::vector<char>> garden(n, std::vector<char>(m));
  for (auto &v : garden) {
    for (auto &e : v) {
      std::cin >> e;
    }
  }

  int count{0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (garden[i][j] == 'w') {
        count++;
        dfs(i, j, garden);
      }
    }
  }
  std::cout << count;
  return 0;
}
