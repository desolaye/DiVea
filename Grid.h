#ifndef GRID_H_
#define GRID_H_

#include <vector>

namespace dv {
template <class Element>
class Grid {
  using Row = std::vector<Element>;

 private:
  int rows_;
  int cols_;
  std::vector<Row> gridBox_;

 public:
  Grid() : Grid(0, 0) {}
  Grid(int dim) : Grid(dim, dim) {}
  Grid(int rows, int cols) : rows_(rows), cols_(cols) {}
  ~Grid() {}
};

}  // namespace dv

#endif  // GRID_H_