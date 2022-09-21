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

  void update(sf::RenderWindow *w, sf::Event &e) {
    sf::Vector2i MousePos = sf::Mouse::getPosition(*w);

    if (isHovered(MousePos)) {
      if (!isBtnHovered_) {
        shape_.setFillColor(sf::Color(32, 32, 32));
        isBtnHovered_ = true;
      }

      if (isClicked(e)) {
        isBtnPressed_ = true;
        std::cout << text_.getString().toAnsiString() << std::endl;
      } else if (e.type != sf::Event::MouseButtonReleased && isBtnPressed_) {
        isBtnPressed_ = false;
      }
    }

    if (!isHovered(MousePos) && isBtnHovered_) {
      shape_.setFillColor(sf::Color(16, 16, 16));
      isBtnHovered_ = false;
    }
  }

  void setPosition(float x, float y) {
    shape_.setPosition(x, y);

    float pos_text_x = (x + shape_.getGlobalBounds().width / 2.f) -
                       (text_.getGlobalBounds().width / 2.f);

    float pos_text_y = (y + shape_.getGlobalBounds().height / 2.5f) -
                       (text_.getGlobalBounds().height / 2.f);

    text_.setPosition(pos_text_x, pos_text_y);
  }

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