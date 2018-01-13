#include "cell.h"

#include "common.h"
#include "display.h"

namespace game {

Cell::~Cell() {}

void Cell::set_position(int x, int y) {
  x_ = x;
  y_ = y;
}

void Cell::set_object(Object* obj) {
  obj_ = obj;
}

void Cell::notify_display(Display &display) {
  char type = ' ';
  if (obj_) {
    int type_self = obj_->get_type();
    if (obj_) {
      if (type_self == kHorizontalWall) {
        type = '-';
      } else if (type_self == kVerticalWall) {
        type = '|';
      } else if (type_self == kGround) {
        type = '|';
      } else if (type_self == kDoor) {
        type = '|';
      } else if (type_self == kPassage) {
        type = '|';
      } else if (type_self == kStairway) {
        type = '|';
      } else if ((type_self & kMaskPlayer) == kPlayer) {
        type = '@';
      } else if (type_self == kEnemyDragon) {
        type = 'D';
      } else if (type_self == kEnemyGoblin) {
        type = 'g';
      } else if (type_self == kEnemyGridBug) {
        type = 'X';
      } else if (type_self == kEnemyMerchant) {
        type = 'M';
      } else if (type_self == kEnemyOrc) {
        type = 'O';
      } else if ((type_self & kMaskTreasure) == kTreasure) {
        type = '$';
      } else if ((type_self & kMaskPotion) == kPotion) {
        type = '!';
      }
    }
  }
  display.change(x_, y_, type);
}

} //namespace game
