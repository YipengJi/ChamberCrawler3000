#ifndef WD_H_
#define WD_H_

#include "potion.h"

namespace game {

class WD : public Potion {
 public:
  WD() {}
  virtual ~WD() {}
    virtual int get_type() { return kPotionWD; }
    virtual void use_potion(Player* player);
};

} //namespace game

#endif //WD_H_

