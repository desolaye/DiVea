#ifndef VIEW_H_
#define VIEW_H_

#include <SFML/Graphics.hpp>

#include "../Controller.h"

namespace dv {

class View : public sf::Drawable {
 private:
  Controller* controller_;
  Display* display_ = nullptr;
  Input* inputX_ = nullptr;
  std::vector<std::vector<Button>>* standartBtns_ = nullptr;
  std::vector<std::vector<Button>>* extendedBtns_ = nullptr;

 public:
  View(Controller* c) : controller_(c) {
    standartBtns_ = controller_->getStandartBtns();
    extendedBtns_ = controller_->getExtendedBtns();
    display_ = controller_->getDisplay();
    inputX_ = controller_->getInputX();
  }

  ~View() {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*display_, states);

    for (auto& row : *standartBtns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }

    for (auto& row : *extendedBtns_) {
      for (auto& btn : row) {
        target.draw(btn);
      }
    }

    target.draw(*inputX_);
  }
};

}  // namespace dv

#endif  // VIEW_H_