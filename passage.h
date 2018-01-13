#ifndef PASSAGE_H_
#define PASSAGE_H_

namespace game {

class Passage : public FloorUnit {
 public:
  Passage() : FloorUnit(kPassage) {}
};

} //namespace game

#endif //PASSAGE_H_

