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
  double getSquare() override;
  void setParams(std::istream &is);
  bool operator==(const Trap&) const;
  Trap operator=(const Trap&);
  Trap operator++();
  friend std::ostream& operator<<(std::ostream&, const Trap&);
  ~Trap() {};
  
 private:
  double side_a;
  double side_b;
  double side_c;
  double side_d;
  
};

#endif
