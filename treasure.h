#ifndef TREASURE_H_
#define TREASURE_H_

#include "item.h"

namespace game {

class Treasure : public Item {
 public:
    virtual int get_type() = 0;
    virtual int get_value() = 0;
    virtual ~Treasure();
};

} //namespace game

#endif //TREASURE_H_

