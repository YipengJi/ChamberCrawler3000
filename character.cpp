#include "character.h"

#include <stdio.h>
#include <math.h>

#include "common.h"
#include "canvas.h"

namespace game {

Character::~Character() {}

Character::Character(int x, int y, int HP, int attack, int def) 
  : x_(x), y_(y), HP_(HP), HP_max_(HP), attack_(attack),
  defense_(def), is_invisible_(false), is_angry_(true) {}

void Character::set_position(int x, int y) {
  x_ = x;
  y_ = y;
}

void Character::add_attack(int atk) {
  attack_ += atk;
  if (attack_ < 0) {
    attack_ = 0;
  }
}

void Character::add_defense(int def) {
  defense_ += def;
  if (defense_ > 100) {
    defense_ = 100;
  } else if (defense_ < 0) {
    defense_ = 0;
  }
}

void Character::add_HP(int HP) {
  HP_ += HP;
  if (HP_ < 0) {
    HP_ = 0;
  } else if (HP_ > HP_max_) {
    HP_ = HP_max_;
  }
}

std::string Character::attack(std::string direction) {
  std::string dat= direction;
  int next_y = y_;
  int next_x = x_;
  if (dat== "no") {
    next_x--;
  } else if (dat== "so") {
    next_x++;
  } else if (dat== "ea") {
    next_y++;
  } else if (dat== "we") {
    next_y--; 
  } else if (dat== "ne") {
    next_y++;
    next_x--;
  } else if (dat== "nw") {
    next_y--;
    next_x--;
  } else if (dat== "se") {
    next_y++;
    next_x++;
  } else if (dat== "sw") {
    next_y--;
    next_x++;
  } else {
    return "Invalid attack";
  }
  int type = get_type();
  if (get_type() == kPlayerWizard) {
    while(game::Canvas::GetInstance()->get_cell()[next_x][next_y]
        .get_object()->get_type() == kGround) {
      if (dat== "no") {
        next_x--;
      } else if (dat== "so") {
        next_x++;
      } else if (dat== "ea") {
        next_y++;
      } else if (dat== "we") {
        next_y--; 
      } else if (dat== "ne") {
        next_y++;
        next_x--;
      } else if (dat== "nw") {
        next_y--;
        next_x--;
      } else if (dat== "se") {
        next_y++;
        next_x++;
      } else if (dat== "sw") {
        next_y--;
        next_x++;
      }
    }
  }
  return attack(next_x, next_y);
}

std::string Character::attack(int def_x, int def_y) {
  const int length = 1024 * 1024;
  char output[length];
  Factory fac;
  Canvas* can_ = Canvas::GetInstance();
  std::string result = "";
  Object* obj = Canvas::GetInstance()->get_cell()[def_x][def_y].get_object();
  int type_def = obj->get_type();
  if (!obj
      || ((type_def & kMaskItem) == kItem)
      || (type_def & kMaskFlootUnit) == kFloorUnit) {
    return "There is nothing there to attack!";
  }
  Character* def = dynamic_cast<Character*>(Canvas::GetInstance()
      ->get_cell()[def_x][def_y].get_object());
  if (get_type() == kEnemyGridBug && x_ != def_x && y_ != def_y) {
    return "";
  }
  int atk_type = get_type();
  int def_type = def->get_type();
  if (def->get_type() == kEnemyMerchant) {
    def->set_angry(true);
    result += "This is an act of war to every Merchant!\n";
  }
  if (get_type() == kPlayerSamurai) {
    set_invisible(false);
  }
  if (!def->is_invisible() && is_angry()) {
    int damage = ceil(attack_ * (100.0 - def->get_defense()) / 100.0);
    if (def->get_HP() - damage <= 0) {
      def->set_HP(0);
      if ((def->get_type() & kMaskPlayer) == kPlayer) {
        
      } else if ((def->get_type() & kMaskEnemy) == kEnemy ) {
        Object* obj = NULL;
        if (def->get_type() == kEnemyGridBug) {
          obj = fac.create_item(kPotionBA);
        } else if (def->get_type() == kEnemyDragon ) {
          obj = fac.create_floorunit(kGround);
        } else {
          obj = fac.create_item(kTreasureGoldPile);
        }
        //result = get_name(get_type()) + " kill " + get_name(def->get_type());
        result = "The " + get_name(def->get_type()) + " has died.";
        delete def;
        can_->get_cell()[def_x][def_y].set_object(obj);
        can_->get_cell()[def_x][def_y].notify_display(*(can_->get_display()));
        return result;
      }
    } else {
      def->set_HP(def->get_HP() - damage);
      if ((def->get_type() & kMaskPlayer) == kPlayer) {
        snprintf(output, length, "The %s strikes you for %d damage!",
            get_name(get_type()).c_str(),
            damage);
      } else {
        snprintf(output, length, "You attack the %s with your Sword of Segfault for %d damage!",
            get_name(def->get_type()).c_str(),
            damage);
      }
      result += output;
      return result;
    }
  }
  return "";
}

} //namespace game
