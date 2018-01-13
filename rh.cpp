//
//  rh.cpp
//  CC3K
//
//  Created by Caroline Xiao on 2016-03-30.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "rh.h"

namespace game {
    
    void RH::use_potion(Player* player) {
        player->add_HP(30);
    }
    
} //namespace game
