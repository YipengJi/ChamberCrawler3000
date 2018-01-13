#ifndef DRAGON_HOARD_H_
#define DRAGON_HOARD_H_

#include "cell.h"
#include "treasure.h"

namespace game {

class DragonHoard : public Treasure {
 public:
  DragonHoard();
  virtual ~DragonHoard();
  virtual int get_type();
  virtual int get_value();

  void set_cell(Cell* cell);
  Cell* get_cell();

 private:
  Cell* cell_;
};

} //namespace game

#endif //DRAGON_HOARD_H_

