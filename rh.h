#ifndef RH_H_
#define RH_H_

#include "potion.h"

namespace game {

class RH : public Potion {
 public:
  RH() {}
  virtual ~RH() {}
  virtual int get_type() { return kPotionRH; }
  virtual void use_potion(Player* player);
};

} //namespace game

#endif //RH_H_

