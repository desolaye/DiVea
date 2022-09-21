#include "Button.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 800), "Calculator",
                          sf::Style::Close);

  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Green);

  // sf::VertexArray curve(sf::LineStrip);

  // for (int i = -10; i < 20; i++) {
  //   curve.append(sf::Vertex(sf::Vector2f(i + 10, i * i)));
  // }

  std::vector<dv::Button> Buttons;
  Buttons.push_back(dv::Button());
  Buttons.push_back(dv::Button());
  Buttons[0].setString("Ass");
  Buttons[1].setString("Cock");
  Buttons[0].setPosition(100.f, 100.f);
  Buttons[1].setPosition(150.f, 200.f);

  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color(150, 0, 0));
    window.draw(Buttons[0]);
    window.draw(Buttons[1]);
    Buttons[0].update(&window, e);
    Buttons[1].update(&window, e);

    window.display();
  }

  return 0;
}
