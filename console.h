#pragma once

#include <iostream>
#include <vector>
void func();

class console {
public:
  console() = default;
  console(const int n, const int m): data(n, std::string(m, '#')) {}

  void set(int x, int y, char simbol) {
    data[x][y] = simbol;
  }

  void print() {
    for (const auto line : data) {
      std::cout << line;
    }
  }

private:
  std::vector<std::string> data;
};
