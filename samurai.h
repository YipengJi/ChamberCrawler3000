#ifndef SAMURAI_H_
#define SAMURAI_H_

#include "player.h"

namespace game {

class Samurai : public Player {
 public:
  Samurai();
  virtual ~Samurai();
  virtual int get_type();
};

} //namespace game

#endif //SAMURAI_H_
