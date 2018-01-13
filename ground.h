#ifndef Ground_H_
#define Ground_H_

namespace game {

class Ground : public FloorUnit {
 public:
  Ground() : FloorUnit(kGround) {}
};

} //namespace game

#endif //Ground_H_

