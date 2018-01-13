#ifndef WIZARD_H_
#define WIZARD_H_

#include "player.h"

namespace game {

class Wizard : public Player {
 public:
  Wizard() : Player(0, 0, 60, 25, 0) {}
  ~Wizard();
  virtual int get_type();
};

} //namespace game

#endif //WIZARD_H_
