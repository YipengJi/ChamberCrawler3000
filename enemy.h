#ifndef ENEMY_H_
#define ENEMY_H_

#include "character.h"
#include "player.h"

namespace game {

class Enemy : public Character {
 public:
  Enemy(int x, int y, int hp, int atk, int def) : Character(x, y, hp, atk, def) {}
    virtual int get_type() { return kEnemy; }
    //virtual void attack(Player* p) = 0;

 private:

};

} //namespace

#endif //ENEMY_H_
