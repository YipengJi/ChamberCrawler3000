//
//  ba.cpp
//
//  Created by Caroline Xiao on 2016-03-30.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "ba.h"

#include "player.h"

namespace game {

void BA::use_potion(Player* player) {
   player->add_attack(10);
}

} //namespace game
