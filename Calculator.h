#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Display.h"

namespace dv {

class Calculator : public sf::Drawable {
 private:
  sf::RenderWindow* window_;
  Display display_;

 public:
  Calculator(sf::RenderWindow* window) : window_(window) {}
  ~Calculator() {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(display_);
  }

  void update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
    // std::cout << mousePos.x << " " << mousePos.y << std::endl;
  }

  void handleEvents(const sf::Event& e) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      std::cout << "LMB pressed" << std::endl;
    }
  }

  //   void pushLHS();
  //   void pushOperand();
  //   void pushResult();
  //   void setOperator(Type type);
};
}  // namespace dv

#endif  // CALCULATOR_H_