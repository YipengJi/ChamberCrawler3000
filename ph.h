#ifndef PH_H_
#define PH_H_

#include "potion.h"
#include "player.h"
#include "common.h"

namespace game {

class PH : public Potion {
 public:
  PH() {}
  ~PH() {}
  virtual int get_type() { return kPotionPH; }
  virtual void use_potion(Player* player);
};

} //namespace game

#endif //PH_H_



