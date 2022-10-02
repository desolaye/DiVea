#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

#include "Button.h"
#include "Display.h"

namespace dv {

class Calculator : public sf::Drawable {
 private:
  sf::RenderWindow* window_;
  Display display_;
  Button* selectedBtn_;
  std::vector<std::vector<Button>> btns_;
  std::vector<std::vector<Button>> specialBtns_;

 public:
  Calculator(sf::RenderWindow* window) : window_(window) {
    display_.setPosition(sf::Vector2f(0.f, 20.f));
    initButtons();
    initSpecialButtons();
  }

  ~Calculator() {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(display_);

    for (auto& row : btns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }

    for (auto& row : specialBtns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }
  }

  void update() {
    selectedBtn_ = nullptr;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

    for (auto& row : btns_) {
      for (auto& btn : row) {
        if (btn.isHovered(mousePos)) {
          btn.setHover();
          selectedBtn_ = &btn;
        } else {
          btn.setIdle();
        }
      }
    }

    for (auto& row : specialBtns_) {
      for (auto& btn : row) {
        if (btn.isHovered(mousePos)) {
          btn.setHover();
          selectedBtn_ = &btn;
        } else {
          btn.setIdle();
        }
      }
    }
  }

  void handleEvents(const sf::Event& e) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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

        case (T::AC):
          display_.reset();
          break;

        default:
          break;
      }
    }
  }

  void initButtons() {
    btns_.resize(5);
    for (size_t i = 0; i < btns_.size(); ++i) {
      btns_[i].resize(4);
    }

    std::list<std::string> btnChars = {"AC", "",  "%", "-", "1", "2", "3",
                                       "+",  "4", "5", "6", "*", "7", "8",
                                       "9",  "/", "0", "",  ".", "="};

    sf::Vector2f startPos(875.f, 100.f);
    sf::Vector2f gap(5.f, 5.f);
    sf::Vector2f currPos = startPos;
    int expandX = 0;

    for (auto& row : btns_) {
      for (auto& btn : row) {
        if (btnChars.front() == "") {
          btn.setScale(0.f, 0.f);
          btnChars.pop_front();

        } else {
          btn.setText(btnChars.front());
          btnChars.pop_front();

          if (btn.getText() == "AC") {
            btn.setType(T::AC);
            btn.setSize(btn.getSize().x * 2.f + gap.x, btn.getSize().y);

          } else if (btn.getText() == ".") {
            btn.setType(T::Comma);
          } else if (btn.getText() == "0") {
            btn.setType(T::Number);
            btn.setSize(btn.getSize().x * 2.f + gap.x, btn.getSize().y);

          } else if (std::isdigit(btn.getText()[0])) {
            btn.setType(T::Number);
          } else if (btn.getText() == "=") {
            btn.setType(T::Equal);
          } else {
            btn.setType(T::Operand);
          }

          btn.setPosition(currPos);
          currPos.x += btn.getSize().x + gap.x;
        }
      }

      currPos.y += row[0].getSize().y + gap.y;
      currPos.x = startPos.x;
    }
  }

  void initSpecialButtons() {
    specialBtns_.resize(4);
    for (size_t i = 0; i < specialBtns_.size(); ++i) {
      specialBtns_[i].resize(3);
    }

    std::list<std::string> btnChars = {"(",    ")",    "X",    "cos",
                                       "sin",  "tan",  "acos", "asin",
                                       "atan", "sqrt", "ln",   "log"};

    sf::Vector2f startPos(500.f, 180.f);
    sf::Vector2f gap(5.f, 5.f);
    sf::Vector2f currPos = startPos;

    for (auto& row : specialBtns_) {
      for (auto& btn : row) {
        btn.setText(btnChars.front());
        btnChars.pop_front();

        btn.setPosition(currPos);
        btn.setSize(btn.getSize().x * 1.5f, btn.getSize().y);
        currPos.x += btn.getSize().x + gap.x;
      }

      currPos.y += row[0].getSize().y + gap.y;
      currPos.x = startPos.x;
    }
  }

  //   void pushLHS();
  //   void pushOperand();
  //   void pushResult();
  //   void setOperator(Type type);
};
}  // namespace dv

#endif  // CALCULATOR_H_