#ifndef MERCHANT_H_
#define MERCHANT_H_

namespace game {

class Merchant : public Enemy {
 public:
   Merchant() : Enemy(0, 0, 100, 75, 5) {
     set_angry(false);
   }
  virtual int get_type() { return kEnemyMerchant; }
};

} //namespace game

#endif //MERCHANT_H_


