//
// Created by lokot_zxe3r on 28.02.2024.
//

#pragma once
#include "draw.h"

class Snake : private DrawArray {
public:
  Snake() = delete;
  Snake(const float x, const float y, const float s, const int b = 7) : DrawArray() {
    add(new Cyrcle{x, y, s, b});
    size_ = 1;
  }

  ~Snake() override {
    for (auto &i : drawables_) {
      delete i;
    }
  }
  void mag() {
    add(new Cyrcle{drawables_[size_-1]->center().x,drawables_[size_-1]->center().y, drawables_[size_-1]->radius(), drawables_[size_-1]->brightness()});
    ++size_;
  }

  void mag(const int k) {
    for (int i = 0; i < k; ++i) {
      mag();
    }
  }

  void move(const float x, const float y) override {
    buffer_.insert(buffer_.begin(), {x, y});
    drawables_[0]->move(x, y);
    for (int i = 1; i < size_; ++i) {
      if ((drawables_[i]->center() - drawables_[i-1]->center()).mag() > drawables_[i]->radius()*0.9 + drawables_[i-1]->radius()) {
        drawables_[i]->move(buffer_[i].x, buffer_[i].y);
      }
    }
    if (buffer_.size() > size_) {
      buffer_.pop_back();
    }
  }

  void draw(Console &console) const override {
    for (auto &drawElem : drawables_) {
      drawElem->draw(console);
    }
  }

private:
  size_t size_;
  std::vector<Vector2> buffer_{{0,0}};
};
