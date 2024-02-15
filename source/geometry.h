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

  virtual ~Drawable() = default;

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
class Cyrcle : virtual Drawable {
public:
  float radius;

  explicit Cyrcle(const Vector2 &pos, const float rad = 1.0,
                 const char &brightness = ' ', const std::string &name = "")
      : Drawable(Rect{Vector2{pos.x - rad, pos.y - rad},
                      Vector2{pos.x + rad, pos.y + rad}},
                 brightness, name) {
    radius = rad;
  }

  Vector2 center() { return rect_.center(); }

  void draw(Console &console) {
    console.arc(position().x, position().y, radius * scale(), brightness());
  }

private:

};
