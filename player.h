#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "character.h"

namespace game {

class Player : public Character {
 public:
  Player(int x, int y, int hp, int atk, int def)
    : Character(x, y, hp, atk, def), type_prev_(kGround), wallet_(0) {}
  virtual int get_type() = 0;
  virtual ~Player() = 0;

  void add_wallet(int gold) { wallet_ += gold; }
  int get_wallet() const { return wallet_; }
  bool is_alive() const { return get_HP() <= 0; }

  std::string move(std::string direction);
  std::string pickup_item(std::string direction);

 private:
  int wallet_;
  bool is_alive_;
  int type_;
  int type_prev_;
};

} //namespace

#endif //PLAYER_H_
