#ifndef CALCAPP_H_
#define CALCAPP_H_

#include <SFML/Graphics.hpp>

#include "Calculator.h"

namespace dv {

class CalcApp {
 private:
  sf::RenderWindow window_;
  Calculator calculator_;

  void update_() { calculator_.update(); }
  void render_() {
    window_.clear(sf::Color(30, 30, 36));
    window_.draw(calculator_);
    window_.display();
  }

  void handleEvents_() {
    sf::Event e;

    while (window_.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window_.close();
      calculator_.handleEvents(e);
    }
  }

 public:
  CalcApp()
      : window_(sf::VideoMode(1200, 500), "DiVea", sf::Style::Close),
        calculator_(&window_){};
  ~CalcApp(){};

  int run() {
    while (window_.isOpen()) {
      handleEvents_();
      update_();
      render_();
    }

    return 0;
  }
};
}  // namespace dv

#endif  // CALCAPP_H_