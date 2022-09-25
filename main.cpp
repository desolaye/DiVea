#include <string>

#include "Button.h"
#include "Grid.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 800), "DiVea", sf::Style::Close);

  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Green);

  // sf::VertexArray curve(sf::LineStrip);

  // for (int i = -10; i < 20; i++) {
  //   curve.append(sf::Vertex(sf::Vector2f(i + 10, i * i)));
  // }

  sf::Text displayValue;
  std::string displayS = "aboba";
  sf::Font a;
  a.loadFromFile("Raleway.ttf");
  displayValue.setString(displayS);
  displayValue.setFont(a);

  dv::Grid<dv::Button> gr1(3, 3);

  for (int i = 0; i < gr1.getRows(); i++) {
    for (int j = 0; j < gr1.getCols(); j++) {
      gr1.at(i, j) = dv::Button();
      gr1.at(i, j).setString(std::to_string(1 + j + 3 * i));
    }
  }

  gr1.setPosition(0.f, 100.f);
  gr1.init();

  while (window.isOpen()) {
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);
    sf::Event e;

    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color(150, 0, 0));
    window.draw(displayValue);
    window.draw(gr1);
    gr1.update(&MousePos, e, displayS);
    displayValue.setString(displayS);

    window.display();
  }

  return 0;
}
