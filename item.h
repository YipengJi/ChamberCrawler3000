#ifndef ITEM_H_
#define ITEM_H_

#include "object.h"

namespace game {

class Item : public Object{
 public:
    virtual int get_type() = 0;
    virtual ~Item();
};

} //namespace game

#endif //ITEM_H_

