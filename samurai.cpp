#include "samurai.h"

#include "common.h"

namespace game {

Samurai::Samurai() : Player(0, 0, 80, 50, 15) {
  set_invisible(true);
}

Samurai::~Samurai() {}

int Samurai::get_type() {
  return kPlayerSamurai;
}

} //namespace game

