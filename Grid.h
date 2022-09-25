#ifndef GRID_H_
#define GRID_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

namespace dv {
template <class Element>
class Grid : public sf::Drawable {
  using Row = std::vector<Element>;

 private:
  int rows_;
  int cols_;
  sf::Vector2f startPos_;
  std::vector<Row> gridBox_;

 public:
  Grid() : Grid(0, 0) {}
  Grid(int dim) : Grid(dim, dim) {}

  Grid(int rows, int cols) : rows_(rows), cols_(cols) {
    startPos_.x = 0.f;
    startPos_.y = 0.f;
    gridBox_.resize(rows);

    for (int i = 0; i < rows; i++) {
      gridBox_[i].resize(cols);
    }
  }

  ~Grid() {}

  void init() {
    sf::Vector2f currPos = startPos_;

    for (Row& rw : gridBox_) {
      for (Element& el : rw) {
        el.setPosition(currPos.x, currPos.y);
        currPos.x += el.getSize().x;
      }

      currPos.y += rw[cols_ - 1].getSize().y;
      currPos.x = startPos_.x;
    }
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (Row rw : gridBox_) {
      for (Element el : rw) {
        target.draw(el, states);
      }
    }
  }

  void update(sf::Vector2i* MousePos, sf::Event& e) {
    innerUpdate(MousePos, e);
  }

  void update(sf::Vector2i* MousePos, sf::Event& e, std::string& s) {
    innerUpdate(MousePos, e, s);
  }

  void innerUpdate(sf::Vector2i* MousePos, sf::Event& e) {
    for (Row& rw : gridBox_) {
      for (Element& el : rw) {
        el.update(MousePos, e);
      }
    }
  }

  void innerUpdate(sf::Vector2i* MousePos, sf::Event& e, std::string& s) {
    for (Row& rw : gridBox_) {
      for (Element& el : rw) {
        el.update(MousePos, e, s);
      }
    }
  }

  void setPosition(float x, float y) {
    startPos_.x = x;
    startPos_.y = y;
  }

  int getRows() const { return rows_; }
  int getCols() const { return cols_; }

  const Element& at(int row, int col) const { return gridBox_[row][col]; }
  Element& at(int row, int col) { return gridBox_[row][col]; }
};

}  // namespace dv

#endif  // GRID_H_