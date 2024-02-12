//
// Created by lokot_zxe3r on 09.02.2024.
//

#pragma once

#include "math.h"

class point;

class object;

class point {
public:
  point(vector2 coords, char symbol=1) {
    coords_ = coords;
    symbol = symbol;
  }

private:
  vector2 coords_;
  char symbol_;
};
