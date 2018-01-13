#include "display.h"

namespace game {

Display::Display(int width, int height) : width_(width), height_(height) {
  display_ = new char* [height_];
  for (int i=0; i!=height; ++i) {
    display_[i] = new char[width_];
    for (int j=0; j!=width; ++j) {
      display_[i][j] = ' ';
    }
  }
}

void Display::new_level() {
  for (int i=0; i!=height_; ++i) {
    for (int j=0; j!=width_; ++j) {
      display_[i][j] = ' ';
    }
  }
}

Display::~Display() {
  for (int i=0; i!=height_; ++i) {
    delete [] display_[i];
  }
  delete [] display_;
}

void Display::change(int x, int y, char ch) {
  display_[x][y] = ch;
}

std::ostream &operator<<(std::ostream &out, const Display& dis) {
  for (int i=0; i!=dis.height_; ++i) {
    for (int j=0; j!=dis.width_; ++j) {
      out << dis.display_[i][j];
    }
    out << std::endl;
  }
  return out;
}

}
