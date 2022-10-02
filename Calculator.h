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
  std::vector<std::vector<Button>> standartBtns_;
  std::vector<std::vector<Button>> extendedBtns_;
  bool isCommed_ = false;
  bool isOperandLast_ = false;

 public:
  Calculator(sf::RenderWindow* window) : window_(window) {
    display_.setPosition(sf::Vector2f(0.f, 20.f));
    initButtons_();
    initExtendedButtons_();
  }

  ~Calculator() {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(display_);

    for (auto& row : standartBtns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }

    for (auto& row : extendedBtns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }
  }

  void update() {
    selectedBtn_ = nullptr;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

    for (auto& row : standartBtns_) {
      for (auto& btn : row) {
        if (btn.isHovered(mousePos)) {
          btn.setHover();
          selectedBtn_ = &btn;
        } else {
          btn.setIdle();
        }
      }
    }

    for (auto& row : extendedBtns_) {
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
      char lastCh = display_.getLastChar();

      switch (type) {
        case (T::Number):
          handleNumInput_(lastCh);
          break;

        case (T::Comma):
          handleCommaInput_(lastCh);
          break;

        case (T::Operand):
          handleOperandInput_(lastCh);
          break;

        case (T::OBracets):
          handleOBracetsInput_(lastCh);
          break;

        case (T::CBracets):
          handleCBracetsInput_(lastCh);
          break;

        case (T::X):
          handleXInput_(lastCh);
          break;

        case (T::Function):
          handleFuncInput_(lastCh);
          break;

        case (T::AC):
          display_.reset();
          isCommed_ = false;
          isOperandLast_ = false;
          break;

        default:
          break;
      }
    }
  }

 private:
  void initButtons_() {
    standartBtns_.resize(5);
    for (size_t i = 0; i < standartBtns_.size(); ++i) {
      standartBtns_[i].resize(4);
    }

    std::list<std::string> btnChars = {"AC", "%", "^", "*", "1", "2", "3",
                                       "/",  "4", "5", "6", "+", "7", "8",
                                       "9",  "-", "0", "",  ".", "="};

    sf::Vector2f startPos(500.f, 100.f);
    sf::Vector2f gap(5.f, 5.f);
    sf::Vector2f currPos = startPos;

    for (auto& row : standartBtns_) {
      for (auto& btn : row) {
        if (btnChars.front() == "") {
          btn.setScale(0.f, 0.f);
          btnChars.pop_front();

        } else {
          btn.setText(btnChars.front());
          btnChars.pop_front();
          btn.setType(T::Operand);

          if (btn.getText() == "AC") {
            btn.setType(T::AC);
          } else if (btn.getText() == "0") {
            btn.setType(T::Number);
            btn.setSize(btn.getSize().x * 2.f + gap.x, btn.getSize().y);
          } else if (std::isdigit(btn.getText()[0])) {
            btn.setType(T::Number);
          } else if (btn.getText() == "=") {
            btn.setType(T::Equal);
          } else if (btn.getText() == ".") {
            btn.setType(T::Comma);
          }

          btn.setPosition(currPos);
          currPos.x += btn.getSize().x + gap.x;
        }
      }

      currPos.y += row[0].getSize().y + gap.y;
      currPos.x = startPos.x;
    }
  }

  void initExtendedButtons_() {
    extendedBtns_.resize(4);
    for (size_t i = 0; i < extendedBtns_.size(); ++i) {
      extendedBtns_[i].resize(3);
    }

    std::list<std::string> btnChars = {"(",    ")",    "X",    "cos",
                                       "sin",  "tan",  "acos", "asin",
                                       "atan", "sqrt", "ln",   "log"};

    sf::Vector2f startPos(100.f, 180.f);
    sf::Vector2f gap(5.f, 5.f);
    sf::Vector2f currPos = startPos;

    for (auto& row : extendedBtns_) {
      for (auto& btn : row) {
        btn.setText(btnChars.front());
        btnChars.pop_front();

        if (btn.getText() == "(") {
          btn.setType(T::OBracets);
        } else if (btn.getText() == ")") {
          btn.setType(T::CBracets);
        } else if (btn.getText() == "X") {
          btn.setType(T::X);
        } else {
          btn.setType(T::Function);
        }

        btn.setPosition(currPos);
        btn.setSize(btn.getSize().x * 1.5f, btn.getSize().y);
        currPos.x += btn.getSize().x + gap.x;
      }

      currPos.y += row[0].getSize().y + gap.y;
      currPos.x = startPos.x;
    }
  }

  void handleNumInput_(char lastCh) {
    if (lastCh == ')' || lastCh == 'X') {
      display_.addValue("*");
    }
    display_.addValue(selectedBtn_->getText());
    isOperandLast_ = false;
  }

  void handleCommaInput_(char lastCh) {
    if (isOperandLast_) {
      display_.addValue("0");
    }

    if (lastCh == '(') {
      display_.addValue("0");
    }

    if (lastCh == ')' || lastCh == 'X') {
      display_.addValue("*");
      display_.addValue("0");
    }

    if (!isCommed_) {
      display_.addValue(selectedBtn_->getText());
      isCommed_ = !isCommed_;
      isOperandLast_ = false;
    }
  }

  void handleOperandInput_(char lastCh) {
    if (lastCh == '(') {
      display_.addValue("0");
    }

    if (lastCh == '.') {
      display_.replaceLast(selectedBtn_->getText());
      isOperandLast_ = !isOperandLast_;
      isCommed_ = false;

    } else if (!isOperandLast_) {
      display_.addValue(selectedBtn_->getText());
      isOperandLast_ = !isOperandLast_;
      isCommed_ = false;
    } else {
      display_.replaceLast(selectedBtn_->getText());
    }
  }

  void handleOBracetsInput_(char lastCh) {
    isCommed_ = false;
    isOperandLast_ = false;

    if (display_.getText() == "0") {
      display_.setValue(selectedBtn_->getText());
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      display_.addValue("*");
      display_.addValue(selectedBtn_->getText());

    } else if (lastCh == '.') {
      display_.replaceLast("*");
      display_.addValue(selectedBtn_->getText());
    } else {
      display_.addValue(selectedBtn_->getText());
    }
  }

  void handleCBracetsInput_(char lastCh) {
    isCommed_ = false;
    isOperandLast_ = false;

    if (display_.getText() == "0") {
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      display_.addValue(selectedBtn_->getText());
    } else if (lastCh == '(') {
      display_.addValue("0");
      display_.addValue(selectedBtn_->getText());
    } else {
      display_.replaceLast(selectedBtn_->getText());
    }
  }

  void handleXInput_(char lastCh) {
    if (display_.getText() == "0") {
      display_.setValue(selectedBtn_->getText());
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      display_.addValue("*");
      display_.addValue(selectedBtn_->getText());

    } else if (lastCh == '.') {
      display_.replaceLast("*");
      display_.addValue(selectedBtn_->getText());

    } else {
      display_.addValue(selectedBtn_->getText());
    }

    isCommed_ = false;
    isOperandLast_ = false;
  }

  void handleFuncInput_(char lastCh) {
    if (display_.getText() == "0") {
      display_.setValue(selectedBtn_->getText());
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      display_.addValue("*");
      display_.addValue(selectedBtn_->getText());

    } else if (lastCh == '.') {
      display_.replaceLast("*");
      display_.addValue(selectedBtn_->getText());

    } else {
      display_.addValue(selectedBtn_->getText());
    }

    display_.addValue("(");

    isCommed_ = false;
    isOperandLast_ = false;
  }
};
}  // namespace dv

#endif  // CALCULATOR_H_