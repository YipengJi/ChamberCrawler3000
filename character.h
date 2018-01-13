#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>

#include "common.h"
#include "object.h"

namespace game {

class Character : public Object{
 public:
  Character(int x, int y, int HP, int attack, int def);
  virtual ~Character() = 0;

  void set_position(int x, int y);
  void set_HP(int HP) { HP_ = HP; }
  void set_attack(int atk) { attack_ = atk; }
  void set_defense(int def) { defense_ = def; }
  void set_display(char ch) { display_ = ch; }
  void add_attack(int atk);
  void add_defense(int def);
  void add_HP(int HP);

  int get_x() const { return x_; }
  int get_y() const { return y_; }
  int get_HP() const { return HP_; }
  int get_HP_max() const { return HP_max_; }
  int get_attack() const { return attack_; }
  int get_defense() const { return defense_; }
  int get_display() const { return display_; }

  bool is_invisible() const { return is_invisible_; }
  void set_invisible(bool is_invisible) { is_invisible_ = is_invisible; }
  bool is_angry() const { return is_angry_; }
  void set_angry(bool angry) { is_angry_ = angry; }
  
  std::string attack(std::string direction);
  std::string attack(int def_x, int def_y);

  virtual int get_type() = 0;
  
 private:
  int x_;
  int y_;
  int HP_;
  int HP_max_;
  int attack_;
  int defense_;
  //int type_;
  char display_;
  bool is_invisible_;
  bool is_angry_;
};

} //namespace game

#endif //CHARACTER_H_
