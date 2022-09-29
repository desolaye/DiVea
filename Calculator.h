#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Button.h"
#include "Display.h"

namespace dv {

class Calculator : public sf::Drawable {
 private:
  sf::RenderWindow* window_;
  Display display_;
  Button one_;
  Button* selectedBtn_;

 public:
  Calculator(sf::RenderWindow* window) : window_(window), one_(T::Number, "1") {
    display_.setPosition(sf::Vector2f(0.f, 20.f));
    one_.setPosition(sf::Vector2f(0.f, 100.f));
  }

  ~Calculator() {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(display_);
    target.draw(one_);
  }

  void update() {
    selectedBtn_ = nullptr;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
    if (one_.isHovered(mousePos)) {
      one_.setHover();
      selectedBtn_ = &one_;
    } else {
      one_.setIdle();
    }
  }

  void handleEvents(const sf::Event& e) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      std::cout << "LMB pressed" << std::endl;
      handleButtonClick();
    }
  }

  void handleButtonClick() {
    if (selectedBtn_) {
      T type = selectedBtn_->getType();
      switch (type) {
      case (T::Number):
        display_.addValue(selectedBtn_->getText());
        break;
      
      default:
        break;
      }
    }
  }

  //   void pushLHS();
  //   void pushOperand();
  //   void pushResult();
  //   void setOperator(Type type);
};
}  // namespace dv

#endif  // CALCULATOR_H_