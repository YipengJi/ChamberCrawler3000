#ifndef PRNG_H_
#define PRNG_H_

namespace game {

class PRNG {
 private:
   uint32_t  seed_;	// same results on 32/64-bit architectures
 public:
   PRNG( uint32_t  s = 362436069 ) {
     seed_ = s;					// set seed
     assert( ((void)"invalid seed", seed_ != 0) );
   }
   uint32_t seed() {					// read seed
     return seed_;
   }
   void seed( uint32_t  s ) {				// reset seed
     seed_ = s;					// set seed
     assert( ((void)"invalid seed", seed_ != 0) );
   }
   uint32_t operator()() {				// [0,UINT_MAX]
     seed_ = 36969 * (seed_ & 65535) + (seed_ >> 16); // scramble bits
     return seed_;
   }
   uint32_t operator()( uint32_t u ) {			// [0,u]
     assert( ((void)"invalid random range", u < (uint32_t)-1) );
     return operator()() % (u + 1);			// call operator()()
   }
   uint32_t operator()( uint32_t l, uint32_t u ) {	// [l,u]
     assert( ((void)"invalid random range", l <= u) );
     return operator()( u - l ) + l;			// call operator()( uint32_t )
   }
};

} //namespace game

#endif //PRNG_H_
