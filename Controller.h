#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#include "Model/Model.h"
#include "View/Button.h"
#include "View/Display.h"
#include "View/Input.h"

namespace dv {

class Controller {
 private:
  sf::RenderWindow window_;
  Display display_;
  Input inputX_;
  Button* selectedBtn_;
  Model* model_;
  std::vector<std::vector<Button>> standartBtns_;
  std::vector<std::vector<Button>> extendedBtns_;

 public:
  Controller(Model* m) : model_(m) { init(); }
  ~Controller() {}

  sf::RenderWindow& getWindow() { return window_; }

  void handleEvents(const sf::Event& e, sf::Vector2i& mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (selectedBtn_) {
        std::string s = selectedBtn_->getText();
        T type = selectedBtn_->getType();
        model_->handleButtonClick(type, s);
        display_.setValue(model_->getDisplayValue());
      }
    }

    if (e.type == sf::Event::TextEntered && inputX_.isHovered(mousePos)) {
      model_->handleTextInput(e.text.unicode);
      inputX_.setText(model_->getXValue());
    }
  }

  void init() {
    initButtons_();
    initExtendedButtons_();
    initDisplay_();
    // initInputX_();
  }

  void update(sf::Vector2i mousePos) {
    selectedBtn_ = nullptr;

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

    if (inputX_.isHovered(mousePos)) {
      inputX_.setHover();
    } else {
      inputX_.setIdle();
    }
  }

  Input* getInputX() { return &inputX_; }
  Display* getDisplay() { return &display_; }

  std::vector<std::vector<Button>>* getStandartBtns() { return &standartBtns_; }
  std::vector<std::vector<Button>>* getExtendedBtns() { return &extendedBtns_; }

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

  void initDisplay_() { display_.setPosition(sf::Vector2f(0.f, 20.f)); }

  //   void initInputX_() {}
};

}  // namespace dv

#endif  // CONTROLLER_H_