#include "dragon_hoard.h"

#include "common.h"

namespace game {

DragonHoard::DragonHoard() {}

DragonHoard::~DragonHoard() {}

int DragonHoard::get_type() {
  return kTreasureDragonHoard;
}

int DragonHoard::get_value() {
  return kNumDragonHoard;
}

void DragonHoard::set_cell(Cell* cell) {
  cell_ = cell;
}

Cell* DragonHoard::get_cell() {
  return cell_;
}

} //namespace game
