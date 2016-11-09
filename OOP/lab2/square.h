#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include "figure.h"

class Square: public Figure {
 public:
  Square();
  Square(const Square &obj);
  Square(double i);
  Square(std::istream &is);
  
  Square operator++();
  Square operator+(const Square& obj) const;
  friend std::ostream& operator<<(std::ostream& os, const Square& obj);
  friend std::istream& operator>>(std::istream& is, Square& obj);
  bool operator==(const Square& obj) const;
  Square operator=(const Square& obj);
  
  double getSquare() override;
  void Print() override;
  void setParams(std::istream &is);
  ~Square() {};
  
 private:
  double side_a;
};

#endif
