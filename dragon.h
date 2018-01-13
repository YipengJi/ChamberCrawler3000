#ifndef DRAGON_H_
#define DRAGON_H_

#include "cell.h"
#include "enemy.h"

namespace game {

class Dragon : public Enemy {
 public:
  Dragon() : Enemy(0, 0, 150, 50, 10) {}
  virtual int get_type() { return kEnemyDragon; }
  void set_cell(Cell* cell) { cell_ = cell; }
  Cell* get_cell() { return cell_; }

 private:
  Cell* cell_;
};

} //namespace game

#endif //DRAGON_H_

