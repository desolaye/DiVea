#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace dv {

enum class T {
  Number,
  Operand,
  X,
  AC,
  Function,
  Comma,
  Equal,
  Bracets,
  Unknown
};

class Button : public sf::Drawable {
 private:
  sf::RectangleShape shape_;
  sf::Text text_;
  sf::Font font_;
  T type_;

 public:
  Button() : Button(T::Unknown, "") {}
  Button(T type, std::string s) : type_(type) {
    shape_.setSize(sf::Vector2f(75.f, 75.f));
    shape_.setFillColor(sf::Color(52, 52, 62));

    font_.loadFromFile("RobotoMono.ttf");
    text_.setFont(font_);
    text_.setString(s);
    text_.setFillColor(sf::Color::White);
    text_.setCharacterSize(24);

    setTextPosition();
  }

  ~Button() {}

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape_, states);
    target.draw(text_, states);
  }

  void setSize(float x, float y) {
    shape_.setSize(sf::Vector2f(x, y));
    setTextPosition();
  }

  void setPosition(float x, float y) {
    shape_.setPosition(x, y);
    setTextPosition();
  }

  void setHover() { shape_.setFillColor(sf::Color(132, 132, 132)); }
  void setIdle() { shape_.setFillColor(sf::Color(52, 52, 62)); }

  void setPosition(sf::Vector2f v) {
    shape_.setPosition(v);
    setTextPosition();
  }

  void setText(std::string s) {
    text_.setString(s);
    setTextPosition();
  }

  void setType(T type) { type_ = type; }

  void setTextPosition() {
    sf::Vector2f pos = shape_.getPosition();

    float pos_text_x = (pos.x + shape_.getGlobalBounds().width / 2.f) -
                       (text_.getGlobalBounds().width / 2.f);
    float pos_text_y = (pos.y + shape_.getGlobalBounds().height / 2.5f) -
                       (text_.getGlobalBounds().height / 2.f);

    text_.setPosition(pos_text_x, pos_text_y);
  }

  void setScale(float x, float y) { shape_.setScale(x, y); }

  bool isHovered(sf::Vector2i MousePos) const {
    return shape_.getGlobalBounds().contains(MousePos.x, MousePos.y);
  }

  std::string getText() const { return text_.getString().toAnsiString(); }

  T getType() const { return type_; }

  sf::Vector2f getSize() const { return shape_.getSize(); }
};

}  // namespace dv

#endif  // BUTTON_H_