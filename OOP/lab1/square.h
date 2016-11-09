#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"

class Squar: public Figure{
 public:
  Squar();
  Squar(const Squar &obj);
  Squar(double i);
  Squar(std::istream &is);
  double Square() override;
  void Print() override;
  void setParams(std::istream &is);
  ~Squar() {};
  
 private:
  double side_a;
};

#endif
