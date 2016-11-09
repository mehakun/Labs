#include "square.h"

Squar::Squar() : Squar(0){}
Squar::Squar(const Squar &obj) {
  side_a = obj.side_a;
}

Squar::Squar(double i) {
  this->side_a = i;
  std::cout << "Square created: "  << this->side_a << std::endl;
}

Squar::Squar(std::istream &is) {
  is >> this->side_a;
}

double Squar::Square() {
  return this->side_a * this->side_a;
}

void Squar::setParams(std::istream &is) {
  is >> this->side_a;
}

void Squar::Print() {
  std::cout << "Type of figure is square" << std::endl
            << "a = " << this->side_a << std::endl;
}

