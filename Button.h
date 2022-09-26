#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include <iostream>

namespace dv {
class Button : public sf::Drawable {
 private:
  sf::RectangleShape shape_;
  sf::Text text_;
  sf::Font font_;
  bool isBtnPressed_ = false;
  bool isBtnHovered_ = false;

 public:
  Button() {
    shape_ = sf::RectangleShape({150.f, 100.f});
    shape_.setFillColor(sf::Color(16, 16, 16));
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
        if (getText() == "C") {
          s = "";
        } else {
          s += getText();
        }
      } else if (e.type != sf::Event::MouseButtonReleased && isBtnPressed_) {
        isBtnPressed_ = false;
      }
    }

    if (!isHovered(*MousePos) && isBtnHovered_) {
      shape_.setFillColor(sf::Color(16, 16, 16));
      isBtnHovered_ = false;
    }
  }

  void setSize(float x, float y) {
    shape_.setSize(sf::Vector2f(x, y));
    setTextPosition();
  }

  std::string getText() { return text_.getString().toAnsiString(); }

  void setPosition(float x, float y) {
    shape_.setPosition(x, y);
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

  sf::Vector2f getSize() const { return shape_.getSize(); }

  void setString(std::string s) {
    text_.setString(s);
    font_.loadFromFile("Raleway.ttf");
    text_.setFont(font_);
  }

  bool isHovered(sf::Vector2i MousePos) const {
    return shape_.getGlobalBounds().contains(MousePos.x, MousePos.y);
  }

  bool isClicked(sf::Event e) const {
    return e.type == sf::Event::MouseButtonReleased && !isBtnPressed_;
  }
};

}  // namespace dv

#endif  // BUTTON_H_