//
// Created by lokot_zxe3r on 12.02.2024.
//

#pragma once

template<typename Type>
class basic_vector2;



typedef basic_vector2<int> vector2;

typedef basic_vector2<int> vector2;

template<typename Type>
class basic_vector2 {
public:
  basic_vector2() = default;
  basic_vector2(Type a, Type b) {
    x_ = a;
    y_ = b;
  }

  basic_vector2(const basic_vector2 &other) {
    x_ = other.x_;
    y_ = other.y_;
  }

  Type X() const {
    return x_;
  }

  Type Y() const {
    return y_;
  }

  basic_vector2 &operator=(const basic_vector2 &other) {
    if (*this == other) {
      return *this;
    }
    x_ = other.X();
    y_ = other.Y();
    return *this;
  }

  bool operator==(const basic_vector2 &other) {
    return (this->X() == other.X() && this->Y() == other.Y());
  }

  friend basic_vector2 operator+(const basic_vector2 &a, const basic_vector2 &b) {
    return basic_vector2{a.X + b.X, a.Y + b.Y};
  }

  friend basic_vector2 operator*(const basic_vector2 &a, const Type &n) {
    return basic_vector2{a.X * n, a.Y * n};
  }

  friend basic_vector2 operator*(const Type &n, const basic_vector2 &a) {
    return basic_vector2{a.X * n, a.Y * n};
  }

  float length() {
    return std::sqrt(x_*x_ + y_*y_);
  }

private:
  Type x_;
  Type y_;
};
