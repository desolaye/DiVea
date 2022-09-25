#include "Button.h"
#include "Grid.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 800), "Calculator",
                          sf::Style::Close);

  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Green);

  // sf::VertexArray curve(sf::LineStrip);

  // for (int i = -10; i < 20; i++) {
  //   curve.append(sf::Vertex(sf::Vector2f(i + 10, i * i)));
  // }

  dv::Grid<dv::Button> gr1(1, 3);

  gr1.at(0, 0) = dv::Button();
  gr1.at(0, 1) = dv::Button();
  gr1.at(0, 2) = dv::Button();
  gr1.at(0, 0).setString("1");
  gr1.at(0, 1).setString("2");
  gr1.at(0, 2).setString("3");
  gr1.setPosition(100.f, 0.f);
  gr1.init();

  while (window.isOpen()) {
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);
    sf::Event e;

    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color(150, 0, 0));

    window.draw(gr1);
    gr1.update(&MousePos, e);

    window.display();
  }

  return 0;
}
