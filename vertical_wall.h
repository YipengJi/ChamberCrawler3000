#ifndef VERTICAL_WALL_H_
#define VERTICAL_WALL_H_

namespace game {

class VerticalWall : public FloorUnit {
 public:
  VerticalWall() : FloorUnit(kVerticalWall) {}
};

} //namespace game

#endif //VERTICAL_WALL_H_

