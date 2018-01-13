#include "wizard.h"

#include "common.h"

namespace game {

Wizard::~Wizard() {}

int Wizard::get_type() {
  return kPlayerWizard;
}

} //namespace game
