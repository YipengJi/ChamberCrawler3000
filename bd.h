#ifndef BD_H_
#define BD_H_

#include "potion.h"

namespace game {

class BD : public Potion {
 public:
  BD() {}
  ~BD() {}
  virtual int get_type() { return kPotionBD; }
  virtual void use_potion(Player* player);
};

} //namespace game

#endif //BD_H_



