#ifndef STAIREWAY_H_
#define STAIREWAY_H_

#include "floor_unit.h"

namespace game {

class Stairway : public FloorUnit {
 public:
  Stairway() : FloorUnit(kStairway) {}
};

} //namespace game

#endif //STAIREWAY_H_

