#ifndef CHAMBER_H_
#define CHAMBER_H_

#include <vector>

#include "player.h"
#include "cell.h"

namespace game {

class Chamber {
 public:
  Cell* get_cell(int index) { 
    if (index < cells_.size() && index > -1) {
      return cells_[index];
    } else {
      return NULL;
    }
  }
  void clear() { cells_.clear(); }
  int get_size() { return cells_.size(); }
  void push_back(Cell* cell) { cells_.push_back(cell); }
 private:
  int count_;
  std::vector<Cell*> cells_;
};

} //namespace game

#endif //CHAMBER_H_

