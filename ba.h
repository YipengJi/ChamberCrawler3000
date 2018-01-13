#ifndef BA_H_
#define BA_H_

#include "potion.h"

namespace game {
    
class Player;

class BA : public Potion {
 public:
  BA() {}
  ~BA() {}
  virtual int get_type() { return kPotionBA; }
  virtual void use_potion(Player* player);
};

} //namespace game

#endif //BA_H_



