//
// Created by lokot_zxe3r on 09.02.2024.
//
#pragma once

#include <bitset>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "my_math.h"

void func();

class Screen {
public:
  int y_max;
  int x_max;
  int scale = 1;
  Screen() = delete;
  Screen(const int n, const int m) : data_(n, std::vector<uint8_t>(m, 0)) {
    this->y_max = n;
    this->x_max = m;
  }

  void set(const int x, const int y, const uint8_t brightness) {
    data_[y][x] = brightness;
  }

  [[nodiscard]] uint8_t get(const int i, const int j) const {
    return data_[i][j];
  }

  template <typename... Types>
  void withRule(const float x, const float y, const float radius,
                const uint8_t brightness, bool (*rule)(Types...)) {
    float l = std::round(x - radius);
    l = (l - 1 >= 0) ? l - 1 : 0;
    float r = std::round(x + radius);
    r = (r + 1 < x_max) ? r + 1 : x_max - 1;
    float top = std::round(y + radius);
    top = (top + 1 < y_max) ? top + 1 : y_max - 1;
    float bot = std::round(y - radius);
    bot = (bot - 1 >= 0) ? bot - 1 : 0;
    for (float i = l; i <= r; ++i) {
      for (float j = bot; j <= top; ++j) {
        if (rule(x, y, radius, i, j)) {
          set(i, j, brightness);
        }
      }
    }
  }

  template <typename... Types>
  void withRule(const float x, const float y, const float weight,
                const float height, const uint8_t brightness,
                bool (*rule)(Types...)) {
    float l = std::round(x);
    l = (l - 1 >= 0) ? l : 0;
    float r = std::round(x + weight);
    r = (r + 1 < x_max) ? r : x_max - 1;
    float bot = std::round(y + height);
    bot = (bot + 1 < y_max) ? bot : y_max - 1;
    float top = std::round(y);
    top = (top - 1 >= 0) ? top : 0;
    for (float i = l; i < r; ++i) {
      for (float j = top; j < bot; ++j) {
        if (rule(x, y, weight, height, i, j)) {
          set(i, j, brightness);
        }
      }
    }
  }

private:
  std::vector<std::vector<uint8_t>> data_;
};

class Console {
public:
  int y_max;
  int x_max;
  int symbol_n = 8;
  int symbol_m = 4;

  Console() = delete;
  Console(const int n, const int m)
      : data_(n, std::string(m, ' ')), pixelsData_(n * symbol_n, m * symbol_m) {
    this->y_max = n;
    this->x_max = m;
  }

  void set(const int x, const int y, const char symbol) {
    data_[x][y] = symbol;
  }

  void render_display() {
    for (int x_coords = 0; x_coords < x_max * symbol_m; x_coords += symbol_m) {
      for (int y_coords = 0; y_coords < y_max * symbol_n;
           y_coords += symbol_n) {
        int res_distanse = INT_MAX;
        char symbol2print = ' ';
        for (auto &[symbol, matr] : symbols) {
          int sum = 0;
          for (int symbol_x_coords = 0; symbol_x_coords < symbol_m;
               ++symbol_x_coords) {
            for (int symbol_y_coords = 0; symbol_y_coords < symbol_n;
                 ++symbol_y_coords) {
              if (int q = abs(pixelsData_.get(symbol_y_coords + y_coords,
                                              symbol_x_coords + x_coords) -
                              matr[symbol_y_coords][symbol_x_coords])) {
                sum += q;
              }
            }
          }
          if ((res_distanse > sum)) {
            res_distanse = sum;
            symbol2print = symbol;
          }
        }
        set((y_coords / symbol_n), (x_coords / symbol_m), symbol2print);
      }
    }
    clear_screen_();
  }

  void print() const {
    std::ostringstream ss;
    for (const auto &line : data_) {
      ss << line;
    }
    std::cout << ss.str() << std::flush;
  }

  void arc(const float x, const float y, const float radius,
           const uint8_t brightness) {
    pixelsData_.withRule(x, y, radius, brightness, Rules2Draw::arcRule);
  }

  void rect(const float x, const float y, const float weight,
            const float height, const uint8_t brightness) {
    pixelsData_.withRule(x, y, weight, height, brightness,
                         Rules2Draw::rectRule);
  }

private:
  void clear_screen_() {
    pixelsData_ = Screen(y_max * symbol_n, x_max * symbol_m);
  }
  std::vector<std::string> data_;
  Screen pixelsData_;

public:
  std::unordered_map<char, std::array<std::array<uint8_t, 4>, 8>> symbols{
      {32, std::array<std::array<uint8_t, 4>, 8>{{{{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}}}}},
      {179, std::array<std::array<uint8_t, 4>, 8>{{{{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}}}}},
      {180, std::array<std::array<uint8_t, 4>, 8>{{{{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{1, 1, 1, 0}},
                                                   {{1, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}}}}},
      {181, std::array<std::array<uint8_t, 4>, 8>{{{{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{2, 2, 1, 0}},
                                                   {{2, 2, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}},
                                                   {{0, 1, 1, 0}}}}},
      {182, std::array<std::array<uint8_t, 4>, 8>{{{{0, 1, 1, 0}},
                                                   {{0, 4, 4, 0}},
                                                   {{0, 4, 4, 0}},
                                                   {{1, 4, 4, 0}},
                                                   {{1, 4, 4, 0}},
                                                   {{0, 4, 4, 0}},
                                                   {{0, 4, 4, 0}},
                                                   {{0, 4, 4, 0}}}}},
      {43, std::array<std::array<uint8_t, 4>, 8>{{{{0, 0, 0, 0}},
                                                  {{0, 0, 0, 0}},
                                                  {{0, 2, 2, 0}},
                                                  {{2, 2, 2, 2}},
                                                  {{2, 2, 2, 2}},
                                                  {{0, 2, 2, 0}},
                                                  {{0, 2, 2, 0}},
                                                  {{0, 0, 0, 0}}}}},
      {176, std::array<std::array<uint8_t, 4>, 8>{{{{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}},
                                                   {{2, 2, 2, 2}}}}},
      {177, std::array<std::array<uint8_t, 4>, 8>{{{{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}},
                                                   {{4, 4, 4, 4}}}}},
      {178, std::array<std::array<uint8_t, 4>, 8>{{{{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}},
                                                   {{6, 6, 6, 6}}}}},
      {219, std::array<std::array<uint8_t, 4>, 8>{{{{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}}}}},
      {220, std::array<std::array<uint8_t, 4>, 8>{{{{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}}}}},
      {222, std::array<std::array<uint8_t, 4>, 8>{{{{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}},
                                                   {{0, 0, 7, 7}}}}},
      {221, std::array<std::array<uint8_t, 4>, 8>{{{{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}},
                                                   {{7, 7, 0, 0}}}}},
      {223, std::array<std::array<uint8_t, 4>, 8>{{{{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{7, 7, 7, 7}},
                                                   {{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}},
                                                   {{0, 0, 0, 0}}}}},
  };
};
