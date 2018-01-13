#ifndef GOLD_PILE_H_
#define GOLD_PILE_H_

#include "common.h"
#include "treasure.h"

namespace game {

class GoldPile : public Treasure {
 public:
  GoldPile();
  virtual ~GoldPile();
  virtual int get_type();
  virtual int get_value();
};

} //namespace game

#endif //GOLD_PILE_H_

