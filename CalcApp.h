#include "Controller.h"
#include "Model/Model.h"
#include "View/View.h"

namespace dv {

class CalcApp {
 private:
  sf::RenderWindow window_;
  Model* model_;
  View* view_;
  Controller* controller_;

 public:
  CalcApp()
      : window_(sf::VideoMode(1200.f, 500.f), "DiVea 2.0", sf::Style::Close) {
    model_ = new Model();
    controller_ = new Controller(model_);
    view_ = new View(controller_);
  }

  ~CalcApp() {
    delete model_;
    delete view_;
    delete controller_;
  }

  int run() {
    while (window_.isOpen()) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window_);

      handleEvents(mousePos);
      controller_->update(mousePos);
      render();
    }

    return 0;
  }

  void render() {
    window_.clear(sf::Color(30, 30, 36));
    window_.draw(*view_);
    window_.display();
  }

  void handleEvents(sf::Vector2i& mousePos) {
    sf::Event e;

    while (window_.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window_.close();
      controller_->handleEvents(e, mousePos);
    }
  }
};

}  // namespace dv
