//
// Created by lokot_zxe3r on 09.02.2024.
//
#pragma once

#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "my_math.h"

void func();

class Screen {
public:
  int y_max;
  int x_max;
  int scale = 1;
  std::vector<std::vector<uint8_t>> data_;
  Screen() = delete;
  Screen(const int n, const int m) : data_(n, std::vector<uint8_t>(m, 0)) {
    this->y_max = n;
    this->x_max = m;
  }

  void set(const int x, const int y, const uint8_t brightness) {
    data_[x][y] = brightness;
  }

  [[nodiscard]] uint8_t get(const int i, const int j) const {
    return data_[i][j];
  }

  void arc(const float x, const float y, const float radius,
           const uint8_t brightness) {
    int l = std::round(x - radius);
    l = (l >= 0) ? l : 0;
    int r = std::round(x + radius);
    r = (r <= x_max) ? r : x_max;
    int top = std::round(y + radius);
    top = (top <= y_max) ? top : y_max;
    int bot = std::round(y - radius);
    bot = (bot >= 0) ? bot : 0;
    for (int i = l; i <= r; ++i) {
      for (int j = bot; j <= top; ++j) {
        if ((x - i) * (x - i) + (y - j) * (y - j) <= radius * radius) {
          set(j, i, brightness);
        }
      }
    }
  }

private:
};

class Console {
public:
  int y_max;
  int x_max;
  int symbol_n = 8;
  int symbol_m = 4;
  std::map<char, std::bitset<96>> symbols{
      {' ',
       std::bitset<96>("0000000000000000000000000000000000000000000000000000000"
                       "00000000000000000000000000000000000000000")},
      {219,
       std::bitset<96>("1111111111111111111111111111111111111111111111111111111"
                       "11111111111111111111111111111111111111111")},
      {220, std::bitset<96>("00000000000000000000000000000000000000000000000011"
                            "11111111111111111111111111111111"
                            "11111111111111")},
      {221, std::bitset<96>("111111000000"
                            "111111000000"
                            "111111000000"
                            "111111000000"
                            "111111000000"
                            "111111000000"
                            "111111000000"
                            "111111000000")},
      {222, std::bitset<96>("000000111111"
                            "000000111111"
                            "000000111111"
                            "000000111111"
                            "000000111111"
                            "000000111111"
                            "000000111111"
                            "000000111111")},
      {223, std::bitset<96>("111111111111"
                            "111111111111"
                            "111111111111"
                            "111111111111"
                            "000000000000"
                            "000000000000"
                            "000000000000"
                            "000000000000")},
  };

  Console() = delete;
  Console(const int n, const int m)
      : data_(n, std::string(m, ' ')), screen_(n * symbol_n, m * symbol_m) {
    this->y_max = n;
    this->x_max = m;
  }

  void set(const int x, const int y, const char symbol) {
    data_[x][y] = symbol;
  }

  void render_display() {
    for (int x_coords = 0; x_coords < x_max * symbol_m; x_coords += symbol_m) {
      for (int y_coords = 0; y_coords < y_max * symbol_n; y_coords += symbol_n) {
        size_t res_distanse = 97;
        char symbol2print = ' ';
        std::bitset<96> bs;
        std::bitset<96> sup{"00000000000000000000000000000000000000000000000000"
                            "0000000000000000000111"};
        for (int symbol_x_coords = 0; symbol_x_coords < symbol_m;
             ++symbol_x_coords) {
          for (int symbol_y_coords = 0; symbol_y_coords < symbol_n;
               ++symbol_y_coords) {
            bs <<= 3;
            const std::bitset<96> bs_tmp{static_cast<unsigned long>(screen_.get(
                symbol_x_coords + y_coords, symbol_y_coords + x_coords))};
            bs |= (bs_tmp & sup);
               }
             }
        for (auto &[symbol, bitset] : symbols) {
          const size_t distanse = hammingDistance(bitset, bs);
          if (distanse < res_distanse) {
            res_distanse = distanse;
            symbol2print = symbol;
          }
        }
        set((y_coords / symbol_n), (x_coords / symbol_m), symbol2print);
      }
    }
    clear_screen_();
  }

  void print() {
    render_display();
    std::ostringstream ss;
    for (const auto &line : data_) {
      ss << line;
    }
    std::cout << ss.str() << std::flush;
  }

  void arc(const float x, const float y, const float radius,
           const uint8_t brightness) {
    screen_.arc(x, y, radius, brightness);
  }

private:
  void clear_screen_() {
    screen_ = Screen{y_max * symbol_n, x_max * symbol_m};
  }
  std::vector<std::string> data_;
  Screen screen_;
};
