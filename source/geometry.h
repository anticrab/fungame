//
// Created by lokot_zxe3r on 09.02.2024.
//

#pragma once

#include "console.h"
#include "my_math.h"

class Drawable {
public:
  explicit Drawable(const Rect &size = {}, const char &brightness = ' ',
                    const std::string &name = "") {
    rect_ = size;
    brightness_ = brightness;
    scale_ = 1;
    name_ = name;
  }

  virtual ~Drawable() = default;

  virtual void draw(Console &console) const {}

  Rect rect() { return rect_; }

  [[nodiscard]] char brightness() const { return brightness_; }

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

  char brightness_{};
  Rect rect_;
  float scale_{};
  std::string name_;
};

/**
 * Класс для отрисовки окружности
 */
class Cyrcle : public Drawable {
public:
  explicit Cyrcle(const float &posX, const float &posY, const float rad = 1.0,
                  const char &brightness = ' ', const std::string &name = "")
      : Drawable(
            Rect{Vector2{posX - rad, posY - rad}, Vector2{2 * rad, 2 * rad}},
            brightness, name) {
    radius_ = rad;
  }

  [[nodiscard]] Vector2 center() const { return rect_.center(); }

  void center(const float x, const float y) {
    rect_.x(x - radius_);
    rect_.y(y - radius_);
  }

  void draw(Console &console) const override {
    console.arc(center().x, center().y, radius_ * scale(), brightness());
  }

  void radius(const float r) { radius_ = r; }

  [[nodiscard]] float radius() const { return radius_; }

private:
  float radius_;
};

/**
 * Класс для отрисовки точки
 */
class DrawRect : public Drawable {
public:
  explicit DrawRect(const float &posX, const float &posY, const float weight = 1.0, const float height = 1.0,
                    const char &brightness = ' ', const std::string &name = "")
      : Drawable(
            Rect{Vector2{posX, posY }, Vector2{weight, height}},
            brightness, name) {
  }

  [[nodiscard]] Vector2 pos() const { return rect_.pos(); }

  void pos(const float x, const float y) { rect_.pos(x, y); }


  void draw(Console &console) const override {
    console.rect(pos().x, pos().y, rect_.width(), rect_.height(), brightness());
  }

private:
};

class SymbolRect : Drawable {
public:
  SymbolRect(const float &posX1, const float &posY1, const float &posX2,
             const float &posY2, const char symbol, const std::string &name)
      : Drawable(Rect{Vector2{posX1, posY1}, Vector2{posX2, posY2}}, 7, name) {
    symbol_ = symbol;
  }

  void symbol(const char symbol) { symbol_ = symbol; }

  [[nodiscard]] char symbol() const { return symbol_; }

  void draw(Console &console) const override {}

private:
  char symbol_;
};

class DrawArray : public Drawable {
public:
  DrawArray() = default;

  explicit DrawArray(std::vector<Drawable *> &drawables) {
    drawables_ = drawables;
    if (!drawables.empty()) {
      this->rect().x((*std::min_element(drawables.begin(), drawables.end(),
                                        DrawArray::DrawableMinX))
                         ->rect()
                         .left());
      this->rect().y((*std::min_element(drawables.begin(), drawables.end(),
                                        DrawArray::DrawableMinY))
                         ->rect()
                         .top());
      this->rect().width((*std::max_element(drawables.begin(), drawables.end(),
                                            DrawArray::DrawableMaxX))
                             ->rect()
                             .right() -
                         this->rect().x());
      this->rect().height((*std::max_element(drawables.begin(), drawables.end(),
                                             DrawArray::DrawableMaxY))
                              ->rect()
                              .bottom() -
                          this->rect().y());
    }
  }

  static bool DrawableMinX(Drawable *s1, Drawable *s2) {
    return s1->rect().left() < s2->rect().left();
  }
  static bool DrawableMinY(Drawable *s1, Drawable *s2) {
    return s1->rect().top() < s2->rect().top();
  }
  static bool DrawableMaxX(Drawable *s1, Drawable *s2) {
    return s1->rect().right() > s2->rect().right();
  }
  static bool DrawableMaxY(Drawable *s1, Drawable *s2) {
    return s1->rect().bottom() > s2->rect().bottom();
  }

  void draw(Console &console) const override {
    for (auto &drawElem : drawables_) {
      drawElem->draw(console);
    }
  }

  template <typename... Types> void add(Types... args) {
    float x, y, height, widht;
    std::vector<Drawable *> drawables{args...};
    float drawablesX = ((*std::min_element(drawables.begin(), drawables.end(),
                                           DrawArray::DrawableMinX))
                            ->rect()
                            .left());

    float drawablesY = ((*std::min_element(drawables.begin(), drawables.end(),
                                           DrawArray::DrawableMinY))
                            ->rect()
                            .top());

    float drawablesRight =
        ((*std::max_element(drawables.begin(), drawables.end(),
                            DrawArray::DrawableMaxX))
             ->rect()
             .right() -
         this->rect().x());

    float drawablesBottom =
        ((*std::max_element(drawables.begin(), drawables.end(),
                            DrawArray::DrawableMaxY))
             ->rect()
             .bottom() -
         this->rect().y());

    if (drawables_.empty()) {
      x = drawablesX;
      y = drawablesY;
      widht = drawablesRight - x;
      height = drawablesBottom - y;
    } else {
      x = std::min(this->rect().left(), drawablesX);
      y = std::min(this->rect().top(), drawablesY);
      widht = std::max(this->rect().right(), drawablesRight) - x;
      height = std::max(this->rect().bottom(), drawablesBottom) - y;
    }
    this->rect().x(x);
    this->rect().y(y);
    this->rect().width(widht);
    this->rect().height(height);
    for (auto i : drawables) {
      this->drawables_.push_back(i);
    }
  }

private:
  std::vector<Drawable *> drawables_;
};
