//
//  wa.cpp
//  CC3K
//
//  Created by Caroline Xiao on 2016-03-30.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "wa.h"

namespace game {    
    WA::~WA() {}
    
    int WA::get_type() { return kPotionWA; }
    
    void WA::use_potion(Player* player) {
        player->add_attack(-5);
    }
    
} //namespace game
