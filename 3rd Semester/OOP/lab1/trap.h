#ifndef TRAP_H
#define TRAP_H
#include "figure.h"

class Trap: public Figure{
 public:
  Trap();
  Trap(const Trap &obj);
  Trap(double i, double j, double k, double l);
  Trap(std::istream &is);
  void Print() override;
  double Square() override;
  void setParams(std::istream &is);
  ~Trap() {};
  
 private:
  double side_a;
  double side_b;
  double side_c;
  double side_d;
  
};

#endif
