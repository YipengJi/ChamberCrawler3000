#ifndef FLOOR_UNIT_H_
#define FLOOR_UNIT_H_

#include "object.h"
#include "common.h"

namespace game {

class FloorUnit : public Object {
 public:
  FloorUnit(int type) : type_(type) {}
  virtual int get_type() { return type_; }
  virtual ~FloorUnit() {}

 private:
  int type_;
};

} //namespace game

#endif //FLOOR_UNIT_H_
