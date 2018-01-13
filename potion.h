#ifndef POTOIN_H_
#define POTOIN_H_

#include "common.h"
#include "item.h"
#include "player.h"

namespace game {

class Potion : public Item {
 public:
  virtual int get_type() = 0;
  virtual void use_potion(Player* player) = 0;
  virtual ~Potion();
};

} //namespace game

#endif //POTOIN_H_

