#ifndef DOOR_H_
#define DOOR_H_

namespace game {

class Door : public FloorUnit {
 public:
  Door() : FloorUnit(kDoor) {}
};

} //namespace game

#endif //DOOR_H_

