#include "ph.h"

namespace game {

    void PH::use_potion(Player* player) {
        player->add_HP(-30);
    }
    
} //namespace game
