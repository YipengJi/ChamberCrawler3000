#ifndef ORC_H_
#define ORC_H_

namespace game {

class Orc : public Enemy {
 public:
  Orc() : Enemy(0, 0, 120, 30, 30) {}
    virtual int get_type() { return kEnemyOrc; }
    //virtual void attack(Player* p) { }

};

} //namespace game

#endif //ORC_H_


