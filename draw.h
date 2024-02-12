//
// Created by lokot_zxe3r on 09.02.2024.
//

#pragma once

#include "my_math.h"

class point;

class object;

class point {
public:
  point(Vector2 coords, char symbol=1) {
    coords_ = coords;
    symbol = symbol;
  }

private:
  Vector2 coords_;
  char symbol_;
};
