#include "factory.h"

#include "vertical_wall.h"
#include "horizontal_wall.h"
#include "door.h"
#include "passage.h"
#include "stairway.h"
#include "ground.h"

#include "knight.h"
#include "wizard.h"
#include "samurai.h"

#include "dragon.h"
#include "goblin.h"
#include "merchant.h"
#include "orc.h"
#include "grid_bug.h"

#include "item.h"
#include "rh.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "wa.h"
#include "wd.h"
#include "gold_pile.h"
#include "dragon_hoard.h"

namespace game {
    
extern const int kPotionRH;

FloorUnit* Factory::create_floorunit(int type) {
  FloorUnit* tmp = NULL;
  if (kVerticalWall == type) {
    tmp = new VerticalWall();
  } else if (kHorizontalWall == type) {
    tmp = new HorizontalWall();
  } else if (kDoor == type) {
    tmp = new Door();
  } else if (kPassage == type) {
    tmp = new Passage();
  } else if (kStairway == type) {
    tmp = new Stairway();
  } else if (kGround == type) {
    tmp = new Ground();
  }
  return tmp;
}

Player* Factory::create_player(int type) {
  Player* tmp = NULL;
  if (kPlayerKnight == type) {
    tmp = new Knight();
  } else if (kPlayerWizard == type) {
    tmp = new Wizard();
  } else if (kPlayerSamurai == type) {
    tmp = new Samurai();
  }
  return tmp;
}

Item* Factory::create_item(int type) {
  Item* tmp = NULL;
    if (type == kPotionRH) {
    tmp = new RH();
    } else if (type == kPotionBA) {
    tmp = new BA();
    } else if (type == kPotionBD) {
    tmp = new BD();
    } else if (type == kPotionPH) {
        tmp = new PH();
    } else if (type == kPotionWA) {
        tmp = new WA();
    } else if (type == kPotionWD) {
        tmp = new WD();
    } else if (type == kTreasureGoldPile) {
        tmp = new GoldPile();
    } else if (type == kTreasureDragonHoard) {
        tmp = new DragonHoard();
    }
  return tmp;
}

Enemy* Factory::create_enemy(int type)  {
  Enemy* tmp = NULL;
  if (kEnemyDragon == type) {
    tmp = new Dragon();
  } else if (kEnemyGoblin == type) {
    tmp = new Goblin();
  } else if (kEnemyGridBug == type) {
    tmp = new GridBug();
  } else if (kEnemyMerchant == type) {
    tmp = new Merchant();
  } else if (kEnemyOrc == type) {
    tmp = new Orc();
  }
  return tmp;
}

} //namespace game
