#ifndef INPUT_H_
#define INPUT_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace dv {
class Input : public sf::Drawable {
 private:
  sf::RectangleShape shape_;
  sf::Text text_;
  sf::Text placeholder_;
  sf::Text preText_;
  std::string strText_ = "";
  std::string strBefore_ = "";
  sf::Font font_;

 public:
  Input() {
    shape_.setSize(sf::Vector2f(347.5f, 75.f));
    shape_.setFillColor(sf::Color(46, 46, 56));
    shape_.setPosition(sf::Vector2f(100.f, 100.f));

    font_.loadFromFile("RobotoMono.ttf");

    text_.setPosition(sf::Vector2f(140.f, 125.f));
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::White);
    text_.setString(strText_);

    preText_.setCharacterSize(24);
    preText_.setPosition(sf::Vector2f(110.f, 125.f));
    preText_.setFillColor(sf::Color(250, 140, 15));
    preText_.setFont(font_);

    placeholder_.setCharacterSize(24);
    placeholder_.setPosition(sf::Vector2f(140.f, 125.f));
    placeholder_.setFillColor(sf::Color(200, 200, 200, 150));
    placeholder_.setString("Hover to input...");
    placeholder_.setFont(font_);

    setBefore("X: ");
  }

  ~Input() {}

  void setBefore(std::string s) { preText_.setString(s); }
  void setText(std::string s) {
    strText_ = s;
    text_.setString(strText_);
  }

  void setHover() { shape_.setFillColor(sf::Color(36, 36, 48)); }
  void setIdle() { shape_.setFillColor(sf::Color(46, 46, 56)); }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape_, states);
    target.draw(preText_, states);

    if (strText_.length() < 1) {
      target.draw(placeholder_, states);
    } else {
      target.draw(text_, states);
    }
  }

  bool isHovered(sf::Vector2i MousePos) const {
    return shape_.getGlobalBounds().contains(MousePos.x, MousePos.y);
  }

  std::string getStr() { return strText_; }
};

}  // namespace dv

#endif  // INPUT_H_