//
//  wd.cpp
//  CC3K
//
//  Created by Caroline Xiao on 2016-03-30.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "wd.h"

namespace game {
        
    void WD::use_potion(Player* player) {
        player->add_defense(-5);
    }
    
} //namespace game
