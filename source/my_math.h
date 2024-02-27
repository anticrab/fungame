//
// Created by lokot_zxe3r on 12.02.2024.
//

#pragma once

#include <cmath>

class Vector2;
class Rect;

template <typename Type>
size_t hammingDistance(const Type n1, const Type n2) {
  return (n1 ^ n2).count();
}

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

  float operator*(const Vector2 &b) const { return x * b.x + y * b.y; }

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
  Vector2 position{};
  Vector2 size{};
  Rect() = default;
  Rect(const Vector2 &pos, const Vector2 &s) {
    position = pos;
    size = s;
  }

  [[nodiscard]] float width() const { return size.x; }

  void width(const float value) { size.x = value; }

  [[nodiscard]] float height() const { return size.y; }

  void height(const float value) { size.y = value; }

  [[nodiscard]] float left() const { return position.x; }

  [[nodiscard]] float right() const { return position.x + size.x; }

  [[nodiscard]] float top() const { return position.y; }

  [[nodiscard]] float bottom() const { return position.y + size.y; }

  [[nodiscard]] float x() const { return position.x; }

  void x(const float value) { position.x = value; }

  [[nodiscard]] float y() const { return position.y; }

  void y(const float value) { position.y = value; }

  [[nodiscard]] Vector2 center() const {
    return {position.x + size.x / 2, position.y + size.y / 2};
  }

  [[nodiscard]] Vector2 pos() const {
    return position;
  }

  void pos(const float x, const  float y) {
    position.x = x;
    position.y = y;
  }

private:
};