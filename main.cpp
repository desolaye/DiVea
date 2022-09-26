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

  std::string btnChars[16] = {"C", ".", "s", "+", "1", "2", "3", "-", "4", "5", "6", "/", "7", "8", "9", "="};

  dv::Grid<dv::Button> gr1(4, 4);

  for (int i = 0; i < gr1.getRows(); i++) {
    for (int j = 0; j < gr1.getCols(); j++) {
      gr1.at(i, j) = dv::Button();
      gr1.at(i, j).setString(btnChars[j + gr1.getCols() * i]);
    }
  }

  gr1.setPosition(0.f, 200.f);
  gr1.init();

  while (window.isOpen()) {
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);
    sf::Event e;

    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) window.close();
    }

    window.clear(sf::Color(90, 0, 0));
  
    window.draw(displayValue);
    window.draw(gr1);
  
    gr1.update(&MousePos, e, displayS);
    displayValue.setString(displayS);

    window.display();
  }

  return 0;
}
