//
// Created by lokot_zxe3r on 12.02.2024.
//

#pragma once

#include <cmath>
#include <string>

class Vector2;
class Rect;

class Vector2 {
public:
  float x;
  float y;
  Vector2() = default;
  Vector2(float a, float b) {
    x = a;
    y = b;
  }

  Vector2(const Vector2 &other) {
    x = other.x;
    y = other.y;
  }

  Vector2 &operator=(const Vector2 &other) {
    if (*this == other) {
      return *this;
    }
    x = other.x;
    y = other.y;
    return *this;
  }

  bool operator==(const Vector2 &other) const {
    return (x == other.x && y == other.y);
  }

  Vector2 operator+(const Vector2 &b) const {
    return Vector2{x + b.x, y + b.y};
  }

  Vector2 operator-(const Vector2 &b) const {
    return Vector2{x - b.x, y - b.y};
  }

  Vector2 operator*(const float &n) const { return {x * n, y * n}; }

  Vector2 operator/(const float &n) const { return {x / n, y / n}; }

  [[nodiscard]] float mag() const { return std::sqrt(x * x + y * y); }

  [[nodiscard]] Vector2 normolize() const { return (*this) / this->mag(); }

  float operator*(const Vector2 &b) const { return x * b.x() + y * b.y(); }

  [[nodiscard]] float dist(const Vector2 &vec) const {
    return (*this - vec).mag();
  }

  [[nodiscard]] float angle(const Vector2 &vec) const {
    return std::acos(((*this * vec) / (this->mag() * vec.mag())));
  }

  Vector2 rotate(float angle) {
    return {x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle)};
  }

private:
};

class Rect {
public:
  Rect() = default;
  Rect(const Vector2 &pos, const Vector2 &size) {
    position_ = pos;
    size_ = size;
  }

  [[nodiscard]] float width() const { return size_.x; }

  void width(float value) { size_.x = value; }

  [[nodiscard]] float height() const { return size_.y; }

  void height(const float value) { size_.y = value; }

  [[nodiscard]] float left() const { return position_.x; }

  [[nodiscard]] float right() const { return position_.x + size_.x; }

  [[nodiscard]] float top() const { return position_.y; }

  [[nodiscard]] float bottom() const { return position_.y + size_.y; }

  [[nodiscard]] float x() const { return position_.x; }

  void x(const float value) { position_.x = value; }

  [[nodiscard]] float y() const { return position_.y; }

  void y(const float value) { position_.y = value; }

  [[nodiscard]] Vector2 center() const {
    return {position_.x + size_.x / 2, position_.y + size_.y / 2};
  }

private:
  Vector2 position_{};
  Vector2 size_{};
};