#ifndef GRID_BUG_H_
#define GRID_BUG_H_

namespace game {

class GridBug : public Enemy {
 public:
  GridBug() : Enemy(0, 0, 50, 20, 10) {}
    virtual int get_type() { return kEnemyGridBug; }
    //virtual void attack(Player* p) {}

};

} //namespace game

#endif //GRID_BUG_H_

