#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "player.h"

namespace game {

class Knight : public Player {
 public:
  Knight() : Player(0, 0, 100, 50, 50) {};
  virtual ~Knight();
  virtual int get_type();
};

} //namespace game

#endif //KNIGHT_H_
