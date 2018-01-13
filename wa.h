#ifndef WA_H_
#define WA_H_

#include "potion.h"
#include "common.h"

namespace game {

class WA : public Potion {
 public:
    virtual ~WA();
    virtual int get_type();
    virtual void use_potion(Player* player);
};

} //namespace game

#endif //WA_H_


