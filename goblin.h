#ifndef GOBLIN_H_
#define GOBLIN_H_

namespace game {

class Goblin : public Enemy {
 public:
  Goblin() : Enemy(0, 0, 75, 30, 20) {}
    virtual int get_type() { return kEnemyGoblin; }
    //virtual void attack(Player* p) {}
};

} //namespace game

#endif //GOBLIN_H_

