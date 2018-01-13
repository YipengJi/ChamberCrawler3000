#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>

namespace game {

class Display {
 public:
  friend std::ostream &operator<<(std::ostream &out, const Display &display);
  Display(int width, int height);
  ~Display();
  void new_level();
  void change(int x, int y, char ch);

 private:
  char** display_;
  int width_;
  int height_;
};

}

#endif //DISPLAY_H_
