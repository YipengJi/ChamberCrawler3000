//
//  bd.cpp
//  CC3K
//
//  Created by Caroline Xiao on 2016-03-30.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "bd.h"

namespace game {
    
    void BD::use_potion(Player* player) {
        player->add_defense(10);
    }
    
} //namespace game
