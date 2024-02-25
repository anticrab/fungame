//
// Created by lokot_zxe3r on 09.02.2024.
//

#pragma once

#include "console.h"
#include "my_math.h"

class Drawable {
public:
  float scale_;
  std::string name_;

  explicit Drawable(const Rect &size = {}, const char &brightness = ' ',
                    const std::string &name = "") {
    rect_ = size;
    brightness_ = brightness;
    scale_ = 1;
    name_ = name;
  }

  void draw();

  Rect rect() { return rect_; }

  char brightness() const { return brightness_; }

  void brightness(const char &color) { brightness_ = color; }

  [[nodiscard]] Vector2 position() const { return rect_.position; }

  void position(const Vector2 &value) { rect_.position = value; }

  [[nodiscard]] Vector2 size() const { return rect_.size; }

  void size(const Vector2 &value) { rect_.size = value; }

  [[nodiscard]] float scale() const { return scale_; }

  void scale(float value) { scale_ = value; }

  [[nodiscard]] std::string name() const { return name_; }

  void name(const std::string &value) { name_ = value; }

protected:
  void rect(const Rect &value) { rect_ = value; }

  char brightness_;
  Rect rect_;
};

/**
 * Класс для отрисовки точки
 */
class Cyrcle : public Drawable {
public:
  explicit Cyrcle(const Vector2 &pos, const float rad = 1.0,
                 const char &brightness = ' ', const std::string &name = "")
      : Drawable(Rect{Vector2{pos.x - rad, pos.y - rad},
                      Vector2{2 * rad, 2 * rad}},
                 brightness, name) {
    radius_ = rad;
  }

  [[nodiscard]] Vector2 center() const { return rect_.center(); }

  void center(const float x, const float y) {
    rect_.x(x);
    rect_.y(y);
  }

  void draw(Console &console) const {
    console.arc(center().x, center().y, radius_ * scale(), brightness());
  }

  void radius(const float r) {
    radius_ = r;
  }

  [[nodiscard]] float radius() const {
    return radius_;
  }



private:
  float radius_;
};
