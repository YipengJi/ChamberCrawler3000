#ifndef FACTORY_H_
#define FACTORY_H_

#include "floor_unit.h"
#include "player.h"
#include "item.h"
#include "enemy.h"

namespace game {

class Factory {
 public:
  FloorUnit* create_floorunit(int type);
  Player* create_player(int type);
  Item* create_item(int type);
  Enemy* create_enemy(int type);
};

} //namespace game

#endif //FACTORY_H_
