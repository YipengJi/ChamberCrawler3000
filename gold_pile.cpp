#include "gold_pile.h"

namespace game {

GoldPile::GoldPile() {}

GoldPile::~GoldPile() {}

int GoldPile::get_type() {
  return kTreasureGoldPile;
}

int GoldPile::get_value() {
  return kNumGoldPile;
}

} //namespace game

