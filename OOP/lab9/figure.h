#ifndef FIGURE_H
#define FIGURE_H
#include <iostream>
#include <cmath>

class AFigure {
 public:
  virtual double getSquare() = 0;
  virtual void Print() = 0;
  virtual ~AFigure() {};
  virtual int type() = 0;
};

class Figure: public AFigure {
 public:
  double getSquare() {};
  void Print() {};
  int type() {return 0;};
};

#endif
