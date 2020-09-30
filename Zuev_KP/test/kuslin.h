#ifndef ZZ_H__
#define ZZ_H__

#include <iostream>

class ZZ {
private:
  char *data_;
  int ndigits_;
  bool isPositive_;
  ZZ(int val, unsigned int arrsize);
  int realSize() const;
  void convertIn(int val); 

public:
  ZZ(int val=0); 
  ZZ(const ZZ& z);  
  ~ZZ();

  ZZ& operator= (const ZZ& z); 
  friend ZZ operator* (const ZZ& z1, const ZZ& z2);

  friend std::ostream& operator <<(std::ostream& os, const ZZ& z); 

  bool isPositive() const { return isPositive_; } 
  void shrink(); 

  static bool doTrace;
};

#endif

















