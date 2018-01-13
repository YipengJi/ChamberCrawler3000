#ifndef HORIZONTAL_WALL_H_
#define HORIZONTAL_WALL_H_

namespace game {

class HorizontalWall : public FloorUnit {
 public:
  HorizontalWall() : FloorUnit(kHorizontalWall) {}
};

} //namespace game

#endif //HORIZONTAL_WALL_H_

