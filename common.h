#ifndef COMMON_H_
#define COMMON_H_

#include <string>

namespace game {

extern const int kMaskCharacter;
extern const int kCharacter;

extern const int kMaskPlayer;
extern const int kPlayer;

extern const int kPlayerKnight;
extern const int kPlayerWizard;
extern const int kPlayerSamurai;
    
extern const int kMaskEnemy;
extern const int kEnemy;

extern const int kEnemyGridBug;
extern const int kEnemyGoblin;
extern const int kEnemyMerchant;
extern const int kEnemyOrc;
extern const int kEnemyDragon;
    
extern const int kMaskItem;
extern const int kItem;

extern const int kMaskPotion;
extern const int kPotion;

extern const int kPotionRH;
extern const int kPotionBA;
extern const int kPotionBD;
extern const int kPotionPH;
extern const int kPotionWA;
extern const int kPotionWD;
    
extern const int kMaskTreasure;
extern const int kTreasure;
extern const int kTreasureGoldPile;
extern const int kTreasureDragonHoard;
    
extern const int kMaskFlootUnit;
extern const int kFloorUnit;

extern const int kVerticalWall;
extern const int kHorizontalWall;
extern const int kStairway;
extern const int kGround;
extern const int kDoor;
extern const int kPassage;
    
extern const int kNumGoldPile;
extern const int kNumDragonHoard;

extern const int kCountPotion;
extern const int kCountGold;
extern const int kCountEnemy;

extern const int kDisplayWidth;
extern const int kDisplayHeight;

std::string get_name(int type);

} //namespace game

#endif //COMMON_H_

