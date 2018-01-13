//
//  common.cpp
//  CC3K
//
//  Created by Caroline Xiao on 2016-04-01.
//  Copyright © 2016 Caroline Xiao. All rights reserved.
//

#include "common.h"

#include <map>

namespace game {
const int kMaskCharacter = 0x00FF000000;
const int kCharacter = 0x0001000000;

const int kMaskPlayer = 0x00FFFF0000;
const int kPlayer = 0x0001010000;

const int kPlayerKnight = 0x0001010001;
const int kPlayerWizard = 0x0001010002;
const int kPlayerSamurai = 0x0001010003;

const int kMaskEnemy = 0x00FFFF0000;
const int kEnemy = 0x0001020000;

const int kEnemyGridBug = 0x0001020000;
const int kEnemyGoblin = 0x0001020001;
const int kEnemyMerchant = 0x0001020002;
const int kEnemyOrc = 0x0001020003;
const int kEnemyDragon = 0x0001020004;

const int kMaskItem = 0x00FF000000;
const int kItem = 0x0002000000;

const int kMaskPotion = 0x00FFFF0000;
const int kPotion = 0x0002010000;

const int kPotionRH = 0x0002010002;
const int kPotionBA = 0x0002010003;
const int kPotionBD = 0x0002010004;
const int kPotionPH = 0x0002010005;
const int kPotionWA = 0x0002010006;
const int kPotionWD = 0x0002010007;

const int kMaskTreasure = 0x00FFFF0000;
const int kTreasure = 0x0002020000;
const int kTreasureGoldPile = 0x0002020001;
const int kTreasureDragonHoard = 0x0002020002;

const int kMaskFlootUnit = 0x00FF000000;
const int kFloorUnit = 0x0003000000;

const int kVerticalWall = 0x0003000001;
const int kHorizontalWall = 0x0003000002;
const int kStairway = 0x0003000003;
const int kGround = 0x0003000004;
const int kDoor = 0x0003000005;
const int kPassage = 0x000300006;

const int kNumGoldPile = 10;
const int kNumDragonHoard = 50;

const int kCountPotion = 10;
const int kCountGold = 10;
const int kCountEnemy = 20;

const int kDisplayWidth = 79;
const int kDisplayHeight = 25;

std::string get_name(int type) {
  std::map<int, std::string> mp;
  mp[kCharacter] = "Character";

  mp[kPlayer] = "Player";

  mp[kPlayerKnight] = "Knight";
  mp[kPlayerSamurai] = "Samurai";
  mp[kPlayerWizard] = "Wizard";

  mp[kEnemy] = "Enemy";

  mp[kEnemyGridBug] = "GridBug";
  mp[kEnemyGoblin] = "Goblin";
  mp[kEnemyMerchant] = "Merchant";
  mp[kEnemyOrc] = "Orc";
  mp[kEnemyDragon] = "Dragon";

  mp[kItem] = "Item";

  mp[kPotion] = "Potion";

  mp[kPotionBA] = "BA";
  mp[kPotionBD] = "BD";
  mp[kPotionPH] = "PH";
  mp[kPotionRH] = "RH";
  mp[kPotionWA] = "WA";
  mp[kPotionWD] = "WD";

  mp[kTreasure] = "Treasure";

  mp[kTreasureDragonHoard] = "Dragon Horde";
  mp[kTreasureGoldPile] = "Gold Pile";

  mp[kFloorUnit] = "Floor Unit";

  mp[kVerticalWall] = "Vertical Wall";
  mp[kHorizontalWall] = "Horizontal Wall";
  mp[kStairway] = "Stairway";
  mp[kGround] = "Ground";
  mp[kDoor] = "Door";
  mp[kPassage] = "Passage";

  if (mp.count(type) == 1) {
    return mp[type];
  } else {
    return "unknown";
  }

}

} //namespace game
