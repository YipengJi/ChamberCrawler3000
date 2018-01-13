#include "player.h"

#include <stdio.h>

#include <string>
#include <map>

#include "common.h"
#include "canvas.h"
#include "treasure.h"
#include "dragon_hoard.h"
#include "object.h"
#include "potion.h"

namespace game {

Player::~Player() {}

std::string Player::move(std::string direction) {
  char temp[1024];
  bool flag = false;
  std::string result = "unkown";
  int x = Character::get_x();
  int y = Character::get_y();
  int temp_y = y;
  int temp_x = x;
  int type;
  if(direction == "no") {
    temp_x = x - 1;
    result = "You move north.";
  }
  else if(direction == "so") {
    temp_x = x + 1;
    result = "You move south.";
  }
  else if(direction == "ea") {
    temp_y = y + 1;
    result = "You move east.";
  }
  else if(direction == "we") {
    temp_y = y - 1;
    result = "You move west.";
  }
  else if(direction == "ne") {
    temp_x = x - 1;
    temp_y = y + 1;
    result = "You move north-east.";
  }
  else if(direction == "nw") {
    temp_x = x - 1;
    temp_y = y - 1;
    result = "You move north-west.";
  }
  else if(direction == "se") {
    temp_x = x + 1;
    temp_y = y + 1;
    result = "You move south-east.";
  }else if(direction == "sw") {
    temp_x = x + 1;
    temp_y = y - 1;
    result = "You move south-west.";
  }
  else { return "unkown command"; }

  Object* next_obj = Canvas::GetInstance()->get_cell()[temp_x][temp_y].get_object();
  if (next_obj) {
    type = next_obj->get_type();
    if ((type & kMaskTreasure) == kTreasure) {
      if (type == kTreasureDragonHoard) {
        DragonHoard* drghod = dynamic_cast<DragonHoard*>(next_obj);
        if (drghod->get_cell()->get_object()->get_type() != kEnemyDragon) {
          add_wallet(drghod->get_value());
          flag = true;
          snprintf(temp, 1024, "pick up dragon hoard : %d \n", drghod->get_value());
          result = temp;
        }
      } else {
        Treasure* treasure = dynamic_cast<Treasure*>(next_obj);
        add_wallet(treasure->get_value());
          flag = true;
          snprintf(temp, 1024, "pick up gold : %d \n", treasure->get_value());
          result = temp;
      }
    } else if (type == kGround
        || type == kDoor
        || type == kPassage) {
      flag = true;
    } else if (type == kStairway) {
      return "upgrade";
    } else {
      return "You can't move in that direction.";
    }
  } else {
    flag = false;
  }
  Factory fac;
  if (flag) {
    Display* display = Canvas::GetInstance()->get_display();
    Object* tmp = Canvas::GetInstance()->get_cell()[x][y].get_object();
    Canvas::GetInstance()->get_cell()[x][y].set_object(fac.create_floorunit(type_prev_));
    Canvas::GetInstance()->get_cell()[x][y].notify_display(*display);
    if ((type & kTreasure) == kTreasure) {
      type_prev_ = kGround;
    } else {
      type_prev_ = Canvas::GetInstance()->get_cell()[temp_x][temp_y].get_object()->get_type();
    }
    delete Canvas::GetInstance()->get_cell()[temp_x][temp_y].get_object();
    Canvas::GetInstance()->get_cell()[temp_x][temp_y].set_object(tmp);
    Canvas::GetInstance()->get_cell()[temp_x][temp_y].notify_display(*display);
    set_position(temp_x, temp_y);
  }
  return result;
}

std::string Player::pickup_item(std::string direction) {
  char temp[1024];
  std::string result = "There is nothing there to use!";
  int x = Character::get_x();
  int y = Character::get_y();
  int temp_y = y;
  int temp_x = x;
  if(direction == "no") { temp_x = x - 1;  }
  else if(direction == "so") { temp_x = x + 1;  }
  else if(direction == "ea") { temp_y = y + 1;  }
  else if(direction == "we") { temp_y = y - 1;  }
  else if(direction == "ne") { temp_x = x - 1; temp_y = y + 1;  }
  else if(direction == "nw") { temp_x = x - 1; temp_y = y - 1;  }
  else if(direction == "se") { temp_x = x + 1; temp_y = y + 1;  }
  else if(direction == "sw") { temp_x = x + 1; temp_y = y - 1;  }
  else { return "unkown command"; }

  Canvas* can = Canvas::GetInstance();
  Object* obj = can->get_cell()[temp_x][temp_y].get_object();
  int type = obj->get_type();
  Factory fac;
  if ((type & kMaskPotion) == kPotion) {
    std::map<int, std::string> mp;
    mp[kPotionRH] = "Restore Health";
    mp[kPotionBA] = "Boost Attack";
    mp[kPotionBD] = "Boost Defense";
    mp[kPotionPH] = "Poison Health";
    mp[kPotionWA] = "Wound Attack";
    mp[kPotionWD] = "Wound Defense";
    Potion* potion = dynamic_cast<Potion*>(obj);
    potion->use_potion(this);
    result = "You chug the " + mp[potion->get_type()] + " potion.";
    delete obj;
    Object* tmp = fac.create_floorunit(kGround);
    can->get_cell()[temp_x][temp_y].set_object(tmp);
  } else if (type == kTreasureGoldPile) {
    Treasure* treasure = dynamic_cast<Treasure*>(obj);
    add_wallet(treasure->get_value());
    snprintf(temp, 1024, "You pick up the Gold Pile worth %dGP.\n", treasure->get_value());
    result = temp;
    delete obj;
    Object* tmp = fac.create_floorunit(kGround);
    can->get_cell()[temp_x][temp_y].set_object(tmp);
  } else if (type == kTreasureDragonHoard) {
    DragonHoard* drgh = dynamic_cast<DragonHoard*>(obj);
    if (drgh->get_cell()->get_object()->get_type() == kEnemyDragon) {
      result = "It would be foolhardy to take the dragon's gold right now.";
    } else {
      add_wallet(drgh->get_value());
      snprintf(temp, 1024, "You successfully take the Dragon Hoard!\n");
      result = temp;
      delete obj;
      Object* tmp = fac.create_floorunit(kGround);
      can->get_cell()[temp_x][temp_y].set_object(tmp);
    }
  }
  return result;
  }

} //namespace game
