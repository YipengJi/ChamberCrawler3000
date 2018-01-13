#ifndef OBJECT_H_
#define OBJECT_H_

namespace game {

class Object {
 public:
   Object() {}
   virtual int get_type() = 0;
   virtual ~Object() = 0;
};

} //namespace game

#endif //OBJECT_H_
