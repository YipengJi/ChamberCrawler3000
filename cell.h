#ifndef CELL_H_
#define CELL_H_

#include "object.h"
#include "display.h"

namespace game {

class Cell {
 public:
  Cell() {}
  virtual ~Cell();
  void set_position(int x, int y);
  void set_object(Object* obj);
  int get_x() const { return x_; }
  int get_y() const { return y_; }
  Object* get_object() { return obj_; }
  void set_status(bool status) { status_ = status; }
  bool get_status() { return status_; }
  void notify_display(Display &display);

 private:
  int x_;
  int y_;
  Object* obj_;
  bool status_;
};

} //namespace game

#endif //CELL_H_
