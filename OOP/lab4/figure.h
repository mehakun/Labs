#ifndef FIGURE_H
#define FIGURE_H
#include <iostream>
#include <cmath>

class AFigure {
 public:
  virtual double getSquare() = 0;
  virtual void Print() = 0;
  virtual ~AFigure() {};
};

class Figure: public AFigure {
 public:
  double getSquare() {};
  void Print() {};
};

#endif
