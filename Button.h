#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace dv {

enum class T { Number, Operand, X, AC, Function, Comma };
class Button : public sf::Drawable {
 private:
  sf::RectangleShape shape_;
  sf::Text text_;
  sf::Font font_;
  T type_;
  bool isBtnPressed_ = false;
  bool isBtnHovered_ = false;

 public:
  Button(T type, std::string s) {
    shape_.setSize(sf::Vector2f(75.f, 75.f));
    shape_.setFillColor(sf::Color(16, 16, 16));

    font_.loadFromFile("Raleway.ttf");
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

  void update(sf::Vector2i *MousePos, sf::Event &e) {
    if (isHovered(*MousePos)) {
      if (!isBtnHovered_) {
        shape_.setFillColor(sf::Color(32, 32, 32));
        isBtnHovered_ = true;
      }

      if (isClicked(e)) {
        isBtnPressed_ = true;
      } else if (e.type != sf::Event::MouseButtonReleased && isBtnPressed_) {
        isBtnPressed_ = false;
      }
    }

    if (!isHovered(*MousePos) && isBtnHovered_) {
      shape_.setFillColor(sf::Color(16, 16, 16));
      isBtnHovered_ = false;
    }
  }

  void update(sf::Vector2i *MousePos, sf::Event &e, std::string &s) {
    if (isHovered(*MousePos)) {
      if (!isBtnHovered_) {
        shape_.setFillColor(sf::Color(32, 32, 32));
        isBtnHovered_ = true;
      }

      if (isClicked(e)) {
        isBtnPressed_ = true;
      } else if (e.type != sf::Event::MouseButtonReleased && isBtnPressed_) {
        isBtnPressed_ = false;
      }
    }

    if (!isHovered(*MousePos) && isBtnHovered_) {
      shape_.setFillColor(sf::Color(16, 16, 16));
      isBtnHovered_ = false;
    }
  }

  sf::FloatRect getRect() const {
    sf::FloatRect rect = shape_.getGlobalBounds();
    rect.top = sf::Mouse::getPosition().y;
    rect.left = sf::Mouse::getPosition().x;
    return rect;
  }

  void setSize(float x, float y) {
    shape_.setSize(sf::Vector2f(x, y));
    setTextPosition();
  }

  void setPosition(float x, float y) {
    shape_.setPosition(x, y);
    setTextPosition();
  }

  void setPosition(sf::Vector2f v) {
    shape_.setPosition(v);
    setTextPosition();
  }

  void setTextPosition() {
    sf::Vector2f pos = shape_.getPosition();

    float pos_text_x = (pos.x + shape_.getGlobalBounds().width / 2.f) -
                       (text_.getGlobalBounds().width / 2.f);
    float pos_text_y = (pos.y + shape_.getGlobalBounds().height / 2.5f) -
                       (text_.getGlobalBounds().height / 2.f);

    text_.setPosition(pos_text_x, pos_text_y);
  }

  std::string getText() const { return text_.getString().toAnsiString(); }

  void setHover() { shape_.setFillColor(sf::Color(132, 132, 132)); }
  void setIdle() { shape_.setFillColor(sf::Color(32, 32, 32)); }
  T getType() const { return type_; }

  sf::Vector2f getSize() const { return shape_.getSize(); }

  bool isHovered(sf::Vector2i MousePos) const {
    return shape_.getGlobalBounds().contains(MousePos.x, MousePos.y);
  }

  bool isClicked(sf::Event e) const {
    return e.type == sf::Event::MouseButtonReleased && !isBtnPressed_;
  }
};

}  // namespace dv

#endif  // BUTTON_H_