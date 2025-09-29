#include "d1.cpp"
#include "utils.h"
// #include "d10.cpp"
// #include "d11.cpp"
// #include "d13.cpp"
#include "d2.cpp"
#include "d3.cpp"
#include "d4.cpp"
#include "d5.cpp"
#include "d6.cpp"
#include "d7.cpp"
#include "d8.cpp"
#include "d9.cpp"

int main(int argc, char **argv) {
  // clang-format off
  std::map<int, std::function<void()>> puzzles = {
      {1, d1},
      {2, d2},
      {3, d3},
      {4, d4},
      {5, d5},
      {6, d6},
      {7, d7},
      {8, d8},
      {9, d9},
      // {10, d10},
      // {11, d11},
      // {11, d12},
      // {13, d13}
    };

  // clang-format on
  for (auto &[k, v] : puzzles) {
    std::cout << "Day" << k << std::endl;
    v();
  }
  return 0;
}
