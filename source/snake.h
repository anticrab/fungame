//
// Created by lokot_zxe3r on 28.02.2024.
//

#pragma once
#include "draw.h"
#include <experimental/random>

class Apple : public Cyrcle {
public:
  Apple(const float &posX, const float &posY, const float rad = 1.0,
        const int &brightness = 7, const std::string &name = "")
      : Cyrcle{posX, posY, rad, brightness, name} {}

  void rand_coords() {
    const int rx = std::experimental::randint(
        static_cast<int>(radius()*2), static_cast<int>(120 * 4 - radius()*2));
    const int ry = std::experimental::randint(
        static_cast<int>(radius()*2), static_cast<int>(30 * 8 - radius()*2));
    this->center(rx, ry);
  }
};
class Snake : protected DrawArray {
public:
  Snake() = delete;
  Snake(const float x, const float y, const float s, const int b = 7)
      : DrawArray() {
    add(new Cyrcle{x, y, s, b});
    size_ = 1;
  }

  ~Snake() override {
    for (auto &i : drawables_) {
      delete i;
    }
  }
  void mag() {
    add(new Cyrcle{
        drawables_[size_ - 1]->center().x, drawables_[size_ - 1]->center().y,
        drawables_[size_ - 1]->radius(), drawables_[size_ - 1]->brightness()});
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
      if ((drawables_[i]->center() - drawables_[i - 1]->center()).mag() >
          drawables_[i]->radius() * 0.9 + drawables_[i - 1]->radius()) {
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

  [[nodiscard]] bool is_alive_border() const {
    return drawables_[0]->rect().left() >= 0 &&
           drawables_[0]->rect().bottom() <= 30 * 8 &&
           drawables_[0]->rect().right() <= 120 * 4 &&
           drawables_[0]->rect().top() >= 0;
  }

  [[nodiscard]] bool is_alive_body() const {
    if (size_ < 5) {
      return true;
    }
    for (int i = 4; i < size_; ++i) {
      if (drawables_[0]->is_intersect(*drawables_[i])) {
        return false;
      }
    }
    return true;
  }

  [[nodiscard]] Drawable* head() const {
    return drawables_[0];
  }

  bool is_eat_apple(Apple* apple) {
    if (apple->is_intersect(*drawables_[0])) {
      return true;
    }
    return false;
  }

private:
  size_t size_;
  std::vector<Vector2> buffer_{{0, 0}};
};
